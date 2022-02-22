/**
    (CS 219 - Assignment 2) Implementation file of the Interpreter class.
    @file Interpreter.cpp
    @author Lloyd Gonzales
    @version 1.0 1/28/2022
*/

#include "Interpreter.h"

#include <bitset>

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

    // This implicitly removes all whitespace and stores variables as needed
    ss >> operation >> operand_1 >> operand_2;

    // Choose what to do based on the operation.
    // It might be "cleaner" to use an enum or a dict with switch statements
    // But again, I'm erring towards "minimum working" since I don't know what
    // future assignments will require.
    uint32_t result;
    if(operation == "ADD"){
        result = add(operand_1, operand_2);
        
        /*
        // The behavior of the output of an ADD (or any operator) can be varied here.
        // For the sake of this assignment, the output is simply sent to std::cout.
        // It's the same for every other condition.

        // Derived from https://stackoverflow.com/questions/5100718/integer-to-hex-string-in-c
        std::cout << line << " -> "                                                            // Show instruction
                  << "0x" << std::setfill ('0') << std::setw(8) << std::hex << std::uppercase  // Formatting options
                  << result                                                                    // Thing to print out
                  << std::dec << std::endl;                                                    // Reset formatting, flush
        */
    }else if (operation == "AND"){
        result = land(operand_1, operand_2);
    }else if (operation == "ASR"){
        result = asr(operand_1, operand_2);
    }else if (operation == "LSR"){
        result = lsr(operand_1, operand_2);
    }else if (operation == "LSL"){
        result = lsl(operand_1, operand_2);
    }else if (operation == "NOT"){
        result = lnot(operand_1, operand_2);
    }else if (operation == "ORR"){
        result = orr(operand_1, operand_2);
    }else if (operation == "SUB"){
        result = sub(operand_1, operand_2);
    }else if (operation == "XOR"){
        result = lxor(operand_1, operand_2);
    }else{
        throw std::runtime_error("Invalid operation");
    }
    // For now, always default to outputting to cout
    std::cout << line << " -> "                                                            
                << "0x" << std::setfill ('0') << std::setw(8) << std::hex << std::uppercase  
                << result                                                                    
                << std::dec << std::endl;
}

#pragma endregion

#pragma region Operations

/**
    @brief Add two values, returning the value as a uint32_t.

    @param a The first operand as a std::string in hex format.
    @param b The second operand as a std::string in hex format.
    @return a uint32_t with the result of the addition.
*/
uint32_t Interpreter::add(std::string a, std::string b){
    // Derived from:
    // https://stackoverflow.com/questions/1070497/c-convert-hex-string-to-signed-integer
    // https://en.cppreference.com/w/cpp/string/basic_string/stoul

    // It's also possible to have it autodetect, but for now it's explicitly set to hex
    uint32_t operand_1 = std::stoul(a, nullptr, 16);
    uint32_t operand_2 = std::stoul(b, nullptr, 16);

    return operand_1 + operand_2;
}

/**
    @brief Take the bitwise AND of the operands.
    
    @param a The first operand as a std::string in hex format.
    @param b The second operand as a std::string in hex format.
    @return a uint32_t with the result of the bitwise AND.
*/
uint32_t Interpreter::land(std::string a, std::string b){
    uint32_t operand_1 = std::stoul(a, nullptr, 16);
    uint32_t operand_2 = std::stoul(b, nullptr, 16);

    return operand_1 & operand_2;
}

/**
    @brief Perform a 1-bit arithmetic right shift.
    
    @param a The first operand as a std::string in hex format.
    @param b Currently ignored.
    @return a uint32_t with the result of the arithmetic right shift.
*/
uint32_t Interpreter::asr(std::string a, std::string b){
    //begin by assuming it's signed to begin with
    int32_t operand_1 = std::stol(a, nullptr, 16);
    operand_1 = operand_1 >> 1;
    // convince the compiler it's an unsigned without changing bits
    uint32_t* out = reinterpret_cast<uint32_t*>(&operand_1);
    return *out;

    /**
    // convince the compiler this is a signed value without actually changing bits
    //std::cout << std::bitset<32>(operand_1) << std::endl;  
    int32_t* operand = reinterpret_cast<int32_t*>(&operand_1);
    //std::cout << std::bitset<32>(*operand) << std::endl;  
    *operand = *operand >> 1;
    //std::cout << std::bitset<32>(*operand) << std::endl;  
    uint32_t* out = reinterpret_cast<uint32_t*>(operand);
    //std::cout << std::bitset<32>(*out) << std::endl;  
    return *out;
    **/
}

/**
    @brief Perform a 1-bit logical right shift.
    
    @param a The first operand as a std::string in hex format.
    @param b Currently ignored.
    @return a uint32_t with the result of the logical right shift.
*/
uint32_t Interpreter::lsr(std::string a, std::string b){
    uint32_t operand_1 = std::stoul(a, nullptr, 16);

    return operand_1 >> 1;
}

/**
    @brief Perform a 1-bit logical left shift.
    
    @param a The first operand as a std::string in hex format.
    @param b Currently ignored.
    @return a uint32_t with the result of the logical left shift.
*/
uint32_t Interpreter::lsl(std::string a, std::string b){
    uint32_t operand_1 = std::stoul(a, nullptr, 16);

    return operand_1 << 1;
}

/**
    @brief Perform a bitwise NOT.
    
    @param a The first operand as a std::string in hex format.
    @param b Currently ignored.
    @return a uint32_t with the result of the bitwise NOT.
*/
uint32_t Interpreter::lnot(std::string a, std::string b){
    uint32_t operand_1 = std::stoul(a, nullptr, 16);

    return ~operand_1;
}

/**
    @brief Perform a bitwise OR on two operands..
    
    @param a The first operand as a std::string in hex format.
    @param b The second operand as a std::string in hex format.
    @return a uint32_t with the result of the bitwise OR.
*/
uint32_t Interpreter::orr(std::string a, std::string b){
    uint32_t operand_1 = std::stoul(a, nullptr, 16);
    uint32_t operand_2 = std::stoul(b, nullptr, 16);

    return operand_1 | operand_2;    
}

/**
    @brief Subtract two values, returning the value as a uint32_t.
    
    @param a The first operand as a std::string in hex format.
    @param b The second operand as a std::string in hex format.
    @return a uint32_t with the result of the subtraction (a - b).
*/
uint32_t Interpreter::sub(std::string a, std::string b){
    uint32_t operand_1 = std::stoul(a, nullptr, 16);
    uint32_t operand_2 = std::stoul(b, nullptr, 16);

    return operand_1 - operand_2;
}

/**
    @brief Perform a bitwise XOR on two operands.
    
    @param a The first operand as a std::string in hex format.
    @param b The second operand as a std::string in hex format.
    @return a uint32_t with the result of the bitwise XOR.
*/
uint32_t Interpreter::lxor(std::string a, std::string b){
    uint32_t operand_1 = std::stoul(a, nullptr, 16);
    uint32_t operand_2 = std::stoul(b, nullptr, 16);

    return operand_1 ^ operand_2;    
}

#pragma endregion