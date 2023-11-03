cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME tests)
project(${PROJECT_NAME} VERSION 0.1.0 LANGUAGES C CXX)


set(CMAKE_CXX_STANDARD 20)

# find_package(formatCpp REQUIRED)

add_executable(${PROJECT_NAME} tests.cpp)

# Add custom command to run tests during build for the tests
add_custom_command(TARGET tests POST_BUILD
    COMMAND tests -C $<CONFIGURATION> --verbose
)

# target_link_libraries(
#     ${PROJECT_NAME}
#     formatCpp
# )