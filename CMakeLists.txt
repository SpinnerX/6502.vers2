cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME 6502-Emulator)
project(${PROJECT_NAME} VERSION 0.1.0 LANGUAGES C CXX)

# set(CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD 20)

# This is how we are able to simply just include 
# Ref Link: https://stackoverflow.com/questions/8304190/cmake-with-include-and-source-paths-basic-setup

# Ref Link that has the solution: https://stackoverflow.com/questions/73991892/what-is-the-best-way-to-add-assimp-to-a-cmake-project

# This is so we can simply know where the other directories are located in the project
# Such as if we needed to find common we can do ${INCLUDE_DIR}/common instead of manually typing 3DRenderRotator/common
set(PROJECT_INCLUDE_DIR 6502_emulator)
# set(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "" FORCE)
# set(CMAKE_CONFIGURATION_TYPES "Debug" CACHE STRING "" FORCE)
# IF( NOT CMAKE_BUILD_TYPE )
#    SET( CMAKE_BUILD_TYPE Debug ... FORCE )
# ENDIF()
get_property(isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)

if(isMultiConfig)
    if(NOT "Asan" IN_LIST CMAKE_CONFIGURATION_TYPES)
        list(APPEND CMAKE_CONFIGURATION_TYPES Asan)
    endif()
else()
    set(allowedBuildTypes Asan Debug Release RelWithDebInfo MinSizeRel)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "${allowedBuildTypes}")

    if(CMAKE_BUILD_TYPE AND NOT CMAKE_BUILD_TYPE IN_LIST allowedBuildTypes)
        message(FATAL_ERROR "Invalid build type: ${CMAKE_BUILD_TYPE}")
    endif()
endif()

set(CMAKE_C_FLAGS_ASAN
    "${CMAKE_C_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer" CACHE STRING
    "Flags used by the C compiler for Asan build type or configuration." FORCE)

set(CMAKE_CXX_FLAGS_ASAN
    "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer" CACHE STRING
    "Flags used by the C++ compiler for Asan build type or configuration." FORCE)

set(CMAKE_EXE_LINKER_FLAGS_ASAN
    "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -fsanitize=address" CACHE STRING
    "Linker flags to be used to create executables for Asan build type." FORCE)

set(CMAKE_SHARED_LINKER_FLAGS_ASAN
    "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} -fsanitize=address" CACHE STRING
    "Linker lags to be used to create shared libraries for Asan build type." FORCE)

include_directories(
    ${PROJECT_SOURCE_DIR}/${PROJECT_INCLUDE_DIR}/include
)

# Better way instead of GLOBBING 
set(
    all_src
    # ${PROJECT_SOURCE_DIR}/${PROJECT_INCLUDE_DIR}/include/test/Bus.cpp
    # ${PROJECT_SOURCE_DIR}/${PROJECT_INCLUDE_DIR}/include/test/Bus.h
    # ${PROJECT_SOURCE_DIR}/${PROJECT_INCLUDE_DIR}/include/test/olc6502.h
    # ${PROJECT_SOURCE_DIR}/${PROJECT_INCLUDE_DIR}/include/test/olc6502.cpp
    # ${PROJECT_SOURCE_DIR}/${PROJECT_INCLUDE_DIR}/src/cpu/Bus.cpp
    # ${PROJECT_SOURCE_DIR}/${PROJECT_INCLUDE_DIR}/src/cpu/CPU.cpp
    ${PROJECT_SOURCE_DIR}/${PROJECT_INCLUDE_DIR}/src/main.cpp
)

set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

add_subdirectory(tests)

add_executable(
    ${PROJECT_NAME}
    ${all_src}
)


##
## NOTE: To run the unit tests, type the command: "ctest"
## This is what will run our unit tests in thhe test directory
enable_testing()


# Define custom target for running tests during build
add_custom_target(TARGET tests COMMAND tests -C $<CONFIGURATION> --verbose)

add_test(
    NAME tests
    COMMAND tests -C $<CONFIGURATION>
)

include(${PROJECT_SOURCE_DIR}/cmake/glfw.cmake)