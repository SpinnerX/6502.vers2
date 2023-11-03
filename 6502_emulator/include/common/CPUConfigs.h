#pragma once
#include <cstring>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cmath>

/**
 * 
 * CPUConfigs
 * - Contains the registers that'll be used to do operations, moving data, etc.
 * 
 * 
 * Visually to see how it works
 * 
 * whihle loop:
 *  opcode = fetch()
 *  ir = decode(opcode)
 *  
 * 
*/

struct CPUConfigs{
    // Keeping track of our status inside CPUConfigs, since the entire CPU will be utilizing this configurations
    enum Status{
		C = (1 << 0),	// Carry Bit
		Z = (1 << 1),	// Zero
		I = (1 << 2),	// Disable Interrupts
		D = (1 << 3),	// Decimal Mode (unused in this implementation)
		B = (1 << 4),	// Break
		U = (1 << 5),	// Unused
		V = (1 << 6),	// Overflow
		N = (1 << 7),	// Negative
	};

    // resetting these registers to a known state
    void reset(){
        pc = 0x00;
        sp = 0x00;
        x = 0x00;
        y = 0x00;
        ac = 0x00;
        ir = 0x00;
    }

    uint16_t pc = 0x00; // program counter
    uint8_t sp = 0x00; // stack pointer
    uint8_t x = 0x00; // x indexed register
    uint8_t y = 0x00; // y indexed register
    uint8_t ac = 0x00; // accumulator
    uint8_t ir = 0x00; // instruction register. Used during the fetch process. Containing the instruction we are gonna use for decoding
    uint8_t status; // Containing current statuses
};