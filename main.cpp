
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

//top-level interpreter should just keep it as string

//second-level interpreter (actual operation function) can convert strings as necessary

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