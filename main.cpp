#include <iostream>

// CPU Registers
int PC = 0;                // Program Counter
int IR = 0;                // Instruction Register
int Accumulator = 0;       // Accumulator Register

// Memory (for simplicity, an array is used as memory)
int memory[256] = {0};

// Helper function to fetch an instruction from memory based on the program counter value
int fetchInstruction() {
    return memory[PC];
}

// Helper function to fetch an operand value from memory based on the program counter value
int fetchOperand() {
    return memory[PC + 1];
}

// Decode and execute instructions
void decodeAndExecute() {
    IR = fetchInstruction();

    switch (IR) {
        case 0xA9:  // LDA instruction
            Accumulator = fetchOperand();
            break;
        // Add more cases for other instructions here...
        default:
            std::cout << "Invalid instruction detected!\n";
    }
}

// int main() {
//     // Assume memory is pre-initialized with instructions and operand values
//     memory[0] = 0xA9;  // LDA instruction opcode
//     memory[1] = 42;   // Operand value

//     // Fetch Cycle
//     IR = fetchInstruction();   // Fetch the first instruction from memory
//     PC += 1;                   // Increment the program counter

//     // Decode and Execute Cycle
//     switch (IR) {
//         case 0xA9:  // LDA instruction
//             Accumulator = fetchOperand();   // Fetch the operand from memory
//             PC += 1;                        // Increment the program counter
//             break;
//         // Add more cases for other instructions here...
//         default:
//             std::cout << "Invalid instruction detected!\n";
//     }

//     // Print the result
//     std::cout << "Accumulator Value: " << Accumulator << "\n";

//     return 0;
// }


int main() {
    // Assume memory is pre-initialized with instructions and operand values
    memory[0] = 0xA9;  // LDA instruction opcode
    memory[1] = 42;   // Operand value

    // Fetch Cycle
    IR = fetchInstruction();   // Fetch the first instruction from memory
    PC += 1;                   // Increment the program counter

    // Decode and Execute Cycle
    switch (IR) {
        case 0xA9:  // LDA instruction
            Accumulator = fetchOperand();   // Fetch the operand from memory
            PC += 1;                        // Increment the program counter
            break;
        default:
            std::cout << "Invalid instruction detected!\n";
    }

    // Print the result
    std::cout << "Accumulator Value: " << Accumulator << "\n";

    return 0;
}