/**
    (CS 219 - Assignment 1) Driver file.
    @file main.cpp
    @author Lloyd Gonzales
    @version 1.0 1/28/2022
*/
#include "Interpreter.h"

int main(int argc, char *argv[])
{
    std::string filepath;

    if(argc == 2){
        filepath = argv[1];
    }else{
        std::cout << "Usage: ./program <instruction file>" << std::endl;
        return 1;
    }

    // Instantiate the class that'll read instructions
    Interpreter interpreter;

    interpreter.process_instruction_file(filepath);

    return 0;
}
