/**
    (CS 219 - Assignment 2) Header file of the Interpreter class.
    @file Interpreter.h
    @author Lloyd Gonzales
    @version 1.0 1/28/2022
*/

#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <bitset>
#include <algorithm>

/**
    @brief Class for interpreting and executing plaintext assembly, while also storing additional related values
    
    In theory, you could import this into other projects, or spin up multiple Interpreter
    instances - but in reality, it's just an excuse to make registers or other persistent 
    variables easier to work with.
*/
class Interpreter{
private:
    // Registers
    uint32_t r0 = 0;
    uint32_t r1 = 0;
    uint32_t r2 = 0;
    uint32_t r3 = 0;
    uint32_t r4 = 0;
    uint32_t r5 = 0;
    uint32_t r6 = 0;
    uint32_t r7 = 0;
public:
    void process_instruction_file(std::string filepath);
    void interpret_line(std::string line);
    uint32_t* string_to_register_pointer(std::string reg);
    uint32_t immediate_to_int(std::string Imm);

    void add(std::string Rd, std::string Rn, std::string Rm);
    void land(std::string Rd, std::string Rn, std::string Rm);
    void asr(std::string Rd, std::string Rn);
    void lsr(std::string Rd, std::string Rn);
    void lsl(std::string Rd, std::string Rn);
    void orr(std::string Rd, std::string Rn, std::string Rm);
    void sub(std::string Rd, std::string Rn, std::string Rm);
    void lxor(std::string Rd, std::string Rn, std::string Rm);

    void mov(std::string Rd, std::string Imm);
};

#endif