/**
    (CS 219 - Assignment 2) Implementation file of the Interpreter class.
    @file Interpreter.cpp
    @author Lloyd Gonzales
    @version 1.0 1/28/2022
*/

#include "Interpreter.h"



#pragma region Core
/**
    Process an entire file, running until the end of the file is reached (or some other terminating condition).
    @param filepath The filepath of the file to process.
*/
void Interpreter::process_instruction_file(std::string filepath){
    // Derived from https://stackoverflow.com/questions/7868936/read-file-line-by-line-using-ifstream-in-c
    std::ifstream file_obj(filepath);
    std::string line;

    // Read a file, line-by-line.
    // If it's necessary to jump lines, this could be replaced with some solution from here:
    // https://stackoverflow.com/questions/5207550/in-c-is-there-a-way-to-go-to-a-specific-line-in-a-text-file
    // It also seems the convention is fixed-width lines, so it may be possible to do it the "fast" way
    while (std::getline(file_obj, line)){
        interpret_line(line);
    }
}

/**
    Interpret a single instruction (line).
    @param line The instruction to process.
*/
void Interpreter::interpret_line(std::string line){
    // Begin by converting all commas to spaces
    // https://www.cplusplus.com/forum/general/33581/
    std::replace(line.begin(), line.end(), ',', ' ');
    // Also, convert full string to uppercase
    // https://stackoverflow.com/questions/735204/convert-a-string-in-c-to-upper-case
    std::transform(line.begin(), line.end(), line.begin(), ::toupper);
    
    // Since interpret_line is a public function that could theoretically be called
    // without respect to a file, everything is a std::string to begin with
    std::stringstream ss;
    ss << line;

    // This assumes there are always three parts to an instruction.
    // Everything stays a string - it's up to the associated operation function
    // to do the work of interpreting an operand.
    std::string operation;
    std::string operand_1;
    std::string operand_2;
    std::string operand_3;

    // This implicitly removes all whitespace and stores variables as needed
    ss >> operation >> operand_1 >> operand_2 >> operand_3;

    // Ignore comments, starting with "; "
    if(operation == ";"){
        return;
    }

    // Choose what to do based on the operation.
    // It might be "cleaner" to use an enum or a dict with switch statements
    // But again, I'm erring towards "minimum working" since I don't know what
    // future assignments will require.
    if(operation == "ADD"){
        add(operand_1, operand_2, operand_3);
    }else if (operation == "AND"){
        land(operand_1, operand_2, operand_3);
    }else if (operation == "ASR"){
        asr(operand_1, operand_2);
    }else if (operation == "LSR"){
        lsr(operand_1, operand_2);
    }else if (operation == "LSL"){
        lsl(operand_1, operand_2);
    }else if (operation == "ORR"){
        orr(operand_1, operand_2, operand_3);
    }else if (operation == "SUB"){
        sub(operand_1, operand_2, operand_3);
    }else if (operation == "XOR"){
        lxor(operand_1, operand_2, operand_3);
    }else if (operation == "MOV"){
        mov(operand_1, operand_2);
    }else{
        throw std::runtime_error("Invalid operation");
    }
}

/**
 * @brief Translate a register "string" (r1, r2, etc.) to the associated register.
 * 
 * @param reg The string to translate.
 * @return uint32_t* A pointer to the associated register.
 * 
 * Use *result = ... to update a register.
 */
uint32_t* Interpreter::string_to_register_pointer(std::string reg){
    if(reg == "R0"){
        return &r0;
    }else if(reg == "R1"){
        return &r1;
    }else if(reg == "R2"){
        return &r2;  
    }else if(reg == "R3"){
        return &r3;
    }else if(reg == "R4"){
        return &r4;
    }else if(reg == "R5"){
        return &r5;
    }else if(reg == "R6"){
        return &r6;
    }else if(reg == "R7"){
        return &r7;
    }else{
        throw std::runtime_error("Invalid register");
    }
}

/**
 * @brief Convert an immediate operand (in #0x... format) to a uint32_t.
 * 
 * @param Imm The immediate operand (in its original form.)
 * @return uint32_t The 32-bit value represented by Imm.
 */
uint32_t Interpreter::immediate_to_int(std::string Imm){
    //begin by stripping out the #, assumed to be the first character
    std::string stripped = Imm.substr(1, std::string::npos);
    return std::stoul(stripped, nullptr, 16);
}

#pragma endregion

#pragma region Operations

/**
    @brief Add Rn and Rm, storing it in Rd.

    @param Rd The destination register.
    @param Rn Operand 1, as a register.
    @param Rm Operand 2, as a register.
*/
void Interpreter::add(std::string Rd, std::string Rn, std::string Rm){
    // Derived from:
    // https://stackoverflow.com/questions/1070497/c-convert-hex-string-to-signed-integer
    // https://en.cppreference.com/w/cpp/string/basic_string/stoul

    // It's also possible to have it autodetect, but for now it's explicitly set to hex
    uint32_t operand_1 = *string_to_register_pointer(Rn);
    uint32_t operand_2 = *string_to_register_pointer(Rm);

    uint32_t* destination_register = string_to_register_pointer(Rd);

    *destination_register = operand_1 + operand_2;

    // Format and output what happened
    std::cout << "ADD " << Rd << ", " << Rn << ", " << Rm << "\n"
              << " -> " << Rd << " = "
              << "0x" << std::setfill ('0') << std::setw(8) << std::hex << std::uppercase
              << *destination_register                                                                    
              << std::dec << std::endl;
}

/**
    @brief Take the bitwise AND of Rn and Rm, storing it in Rd.

    @param Rd The destination register.
    @param Rn Operand 1, as a register.
    @param Rm Operand 2, as a register.
*/
void Interpreter::land(std::string Rd, std::string Rn, std::string Rm){
    uint32_t operand_1 = *string_to_register_pointer(Rn);
    uint32_t operand_2 = *string_to_register_pointer(Rm);

    uint32_t* destination_register = string_to_register_pointer(Rd);

    *destination_register = operand_1 & operand_2;

    // Format and output what happened
    std::cout << "AND " << Rd << ", " << Rn << ", " << Rm << "\n"
              << " -> " << Rd << " = "
              << "0x" << std::setfill ('0') << std::setw(8) << std::hex << std::uppercase
              << *destination_register                                                                    
              << std::dec << std::endl;
}

/**
    @brief Perform a 1-bit arithmetic right shift on Rn, storing it in Rd.
    
    @param Rd The destination register.
    @param Rn The register to perform a shift on.
*/
void Interpreter::asr(std::string Rd, std::string Rn){
    //begin with the unsigned bits
    uint32_t operand_1 = *string_to_register_pointer(Rn);
    // convince the compiler it's a signed without changing bits
    int32_t* step_1 = reinterpret_cast<int32_t*>(&operand_1);
    *step_1 = *step_1 >> 1;
    // make the result unsigned
    uint32_t* step_2 = reinterpret_cast<uint32_t*>(step_1);
    
    //store result in destination register
    uint32_t* destination_register = string_to_register_pointer(Rd);

    *destination_register = *step_2;

    // Format and output what happened
    std::cout << "ASR " << Rd << ", " << Rn << "\n"
              << " -> " << Rd << " = "
              << "0x" << std::setfill ('0') << std::setw(8) << std::hex << std::uppercase
              << *destination_register                                                                    
              << std::dec << std::endl;
}

/**
    @brief Perform a 1-bit logical right shift on Rn, storing it in Rd.
    
    @param Rd The destination register.
    @param Rn The register to perform a shift on.
*/
void Interpreter::lsr(std::string Rd, std::string Rn){
    uint32_t operand_1 = *string_to_register_pointer(Rn);
    
    //store result in destination register
    uint32_t* destination_register = string_to_register_pointer(Rd);

    *destination_register = operand_1 >> 1;

    // Format and output what happened
    std::cout << "LSR " << Rd << ", " << Rn << "\n"
              << " -> " << Rd << " = "
              << "0x" << std::setfill ('0') << std::setw(8) << std::hex << std::uppercase
              << *destination_register                                                                    
              << std::dec << std::endl;
}

/**
    @brief Perform a 1-bit logical left shift on Rn, storing it in Rd.
    
    @param Rd The destination register.
    @param Rn The register to perform a shift on.
*/
void Interpreter::lsl(std::string Rd, std::string Rn){
    uint32_t operand_1 = *string_to_register_pointer(Rn);
    
    //store result in destination register
    uint32_t* destination_register = string_to_register_pointer(Rd);

    *destination_register = operand_1 << 1;

    // Format and output what happened
    std::cout << "LSL " << Rd << ", " << Rn << "\n"
              << " -> " << Rd << " = "
              << "0x" << std::setfill ('0') << std::setw(8) << std::hex << std::uppercase
              << *destination_register                                                                    
              << std::dec << std::endl;
}

/**
    @brief Take the bitwise OR of Rn and Rm, storing it in Rd.

    @param Rd The destination register.
    @param Rn Operand 1, as a register.
    @param Rm Operand 2, as a register.
*/
void Interpreter::orr(std::string Rd, std::string Rn, std::string Rm){
    uint32_t operand_1 = *string_to_register_pointer(Rn);
    uint32_t operand_2 = *string_to_register_pointer(Rm);

    uint32_t* destination_register = string_to_register_pointer(Rd);

    *destination_register = operand_1 | operand_2;

    // Format and output what happened
    std::cout << "ORR " << Rd << ", " << Rn << ", " << Rm << "\n"
              << " -> " << Rd << " = "
              << "0x" << std::setfill ('0') << std::setw(8) << std::hex << std::uppercase
              << *destination_register                                                                    
              << std::dec << std::endl;
}

/**
    @brief Subtract Rm from Rn (Rn - Rm), storing it in Rd.

    @param Rd The destination register.
    @param Rn Operand 1, as a register.
    @param Rm Operand 2, as a register.
*/
void Interpreter::sub(std::string Rd, std::string Rn, std::string Rm){
    uint32_t operand_1 = *string_to_register_pointer(Rn);
    uint32_t operand_2 = *string_to_register_pointer(Rm);

    uint32_t* destination_register = string_to_register_pointer(Rd);

    *destination_register = operand_1 - operand_2;

    // Format and output what happened
    std::cout << "SUB " << Rd << ", " << Rn << ", " << Rm << "\n"
              << " -> " << Rd << " = "
              << "0x" << std::setfill ('0') << std::setw(8) << std::hex << std::uppercase
              << *destination_register                                                                    
              << std::dec << std::endl;
}

/**
    @brief Take the bitwise XOR of Rn and Rm, storing it in Rd.

    @param Rd The destination register.
    @param Rn Operand 1, as a register.
    @param Rm Operand 2, as a register.
*/
void Interpreter::lxor(std::string Rd, std::string Rn, std::string Rm){
    uint32_t operand_1 = *string_to_register_pointer(Rn);
    uint32_t operand_2 = *string_to_register_pointer(Rm);

    uint32_t* destination_register = string_to_register_pointer(Rd);

    *destination_register = operand_1 ^ operand_2;

    // Format and output what happened
    std::cout << "XOR " << Rd << ", " << Rn << ", " << Rm << "\n"
              << " -> " << Rd << " = "
              << "0x" << std::setfill ('0') << std::setw(8) << std::hex << std::uppercase
              << *destination_register                                                                    
              << std::dec << std::endl;
}

/**
    @brief Store Imm in Rd.

    @param Rd The destination register.
    @param Imm The value to load into Rd, as a hex value in the format #0x...
*/
void Interpreter::mov(std::string Rd, std::string Imm){
    uint32_t* destination_register = string_to_register_pointer(Rd);

    *destination_register = immediate_to_int(Imm);
    std::cout << "MOV " << Rd << ", " << Imm << "\n"
            << " -> " << Rd << " = "
            << "0x" << std::setfill ('0') << std::setw(8) << std::hex << std::uppercase
            << *destination_register                                                                    
            << std::dec << std::endl;
}

#pragma endregion