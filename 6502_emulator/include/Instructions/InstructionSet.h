#pragma once
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <common/CPUConfigs.h>



struct BaseInstruction{
    BaseInstruction(std::string n, std::string mode, uint16_t cyc) : name(n), addressMode(mode), cycles(cyc) {}


    virtual void operation(CPUConfigs& configs, uint8_t){
        std::cout << "Default operation() call\n";
    }

    // Will vary if there needs to be an additional cycles for specific instructions
    virtual uint8_t cycle(CPUConfigs&){
        std::cout << "Default cycle() call\n";
        return 0x00;
    }


    friend std::ostream& operator<<(std::ostream& outs, BaseInstruction* rhs){
        outs << "Name: " << rhs->name << '\n';
        outs << "Address Mode: " << rhs->addressMode << '\n';
        outs << "Opcode: " << reinterpret_cast<void*>(rhs->opcode) << '\n';
        outs << "Cycles: " << rhs->cycles << '\n';
        return outs;
    }

    std::string name;
    std::string addressMode;
    uint16_t opcode;
    uint16_t cycles;
};

template<auto x>
struct Instruction;


template<>
struct Instruction<0xA9> : public BaseInstruction{ // Instruction LDA and Address Mode: IMMEDIATE
    Instruction<0xA9>() : BaseInstruction("LDA", "IMM", 2) {}

    // Does the actual operation that LDA does
    void operation(CPUConfigs& configs, uint8_t data){
        configs.ac = data;
    }

    // The additional cycles depend on the address mode this structure is.
    uint8_t cycle(CPUConfigs& configs){
        return 0;
    }
};
