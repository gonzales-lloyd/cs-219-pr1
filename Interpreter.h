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

/**
    @brief Class for interpreting and executing plaintext assembly, while also storing additional related values
    
    In theory, you could import this into other projects, or spin up multiple Interpreter
    instances - but in reality, it's just an excuse to make registers or other persistent 
    variables easier to work with.
*/
class Interpreter{
private:
    // In theory you could put more useful variables here
    // General registers, instruction pointers, etc...
    // But I've left that out since I don't know exactly how future things will look like
    uint32_t last_result = 0;
public:
    void process_instruction_file(std::string filepath);
    void interpret_line(std::string line);

    uint32_t add(std::string a, std::string b);
    uint32_t land(std::string a, std::string b);
    uint32_t asr(std::string a, std::string b);
    uint32_t lsr(std::string a, std::string b);
    uint32_t lsl(std::string a, std::string b);
    uint32_t lnot(std::string a, std::string b);
    uint32_t orr(std::string a, std::string b);
    uint32_t sub(std::string a, std::string b);
    uint32_t lxor(std::string a, std::string b);
};

#endif