
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

//top-level interpreter should just keep it as string

//second-level interpreter (actual operation function) can convert strings as necessary

/**
 * Class for simulating registers, local variables, etc.
 * 
 * In reality, this makes it cleaner because having registers be globals sounds wrong
 */
class Interpreter{
private:
    int last_result = 0;
public:
    void process_instruction_file(std::string filepath);
    void interpret_line(std::string line);
protected:
    uint32_t add(std::string a, std::string b);
};


void Interpreter::process_instruction_file(std::string filepath){
 //https://stackoverflow.com/questions/7868936/read-file-line-by-line-using-ifstream-in-c
}

void Interpreter::interpret_line(std::string line){
    //if ADD: do function, print result to cout
    std::stringstream ss;
    //assume there is always three parts to an instruction

    std::string a;
    std::string b;
    std::string c;

    ss >> a >> b >> c;

    if(a == "ADD"){
        uint32_t result = add(b, c);
        // the behavior of the output of an ADD (or any operator) can be varied here
        std::cout << result;
    }else{
        throw std::runtime_error("Invalid operand");
    }
}

uint32_t Interpreter::add(std::string a, std::string b){
    uint32_t operand_1 = std::stoul(a, nullptr, 16);
    uint32_t operand_2 = std::stoul(b, nullptr, 16);

    return operand_1 + operand_2;
}

int main()
{
    std::string a;
    std::string b;
    std::string c;
     
    std::stringstream ss;

    ss << "ADD       0x12323232               14";
    
    ss >> a >> b >> c;

    //Base is assumed to be 10 by default; you must specify 0 to auto-detect,
    //or explicitly define the base as done here (see the reference)
    uint32_t d = std::stoul(b, nullptr, 16);

    std::cout << a << " " << b << " " << c << " " << d;

    return 0;
}