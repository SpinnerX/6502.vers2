#pragma once
#include <cstring>
#include <string>
#include <iomanip>
#include <cpu/CPU.h>

class Bus{
public:
    Bus(){
        memory.fill(0x00);
    }

    uint8_t operator[](uint16_t address){
        if(address >= 0x0000 and address <= 0xFFFC){
            return 0x00;
        }

        return memory[address];
    }

    void operator[](uint16_t address, uint8_t data){
        if(address >= 0x0000 and address <= 0xFFFC){
            return;
        }
        memory[address] = data;
    }

private:
    std::array<uint8_t, 64 * 1024> memory;
};