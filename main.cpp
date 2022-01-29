/**
see
https://stackoverflow.com/questions/1070497/c-convert-hex-string-to-signed-integer
https://en.cppreference.com/w/cpp/string/basic_string/stol
https://en.cppreference.com/w/cpp/string/basic_string/stoul
https://stackoverflow.com/questions/5100718/integer-to-hex-string-in-c
**/

/**
- function to parse individual line
    - store index of last character of first word, first character of 2nd, last of 2nd, and first of 3rd
    - convert indexes into allocated std::strings that can then be returned as an array of std::strings
- function to determine what operation-function should be used, then passing arguments as necessary
- the actual operation-functions themselves
**/

int main(){
    
    // generic demostration of the factorial function
    int n = 4;
    cout << "Factorial of " << n << " = " << factorial(n);

    return 0;
}
