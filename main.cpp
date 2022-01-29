/**
    (CS 219 - Assignment 1) Driver file.
    @file main.cpp
    @author Lloyd Gonzales
    @version 1.0 1/28/2022
*/
#include "Interpreter.h"

int main()
{
    // Instantiate the class that'll read instructions
    Interpreter interpreter;

    interpreter.process_instruction_file("Programming-Project-1.txt");

    return 0;
}
