/**
    This line is where you decribe the file. And put Cs219 somewhere in here.
    @file code_style.cpp
    @author Shawn Ray
    @version 1.0 1/17/2022
*/

#include<iostream>

using namespace std;

int factorial(int n);

int main(){
    
    // generic demostration of the factorial function
    int n = 4;
    cout << "Factorial of " << n << " = " << factorial(n);

    return 0;
}


/**
    This line is where the function description goes. 
    @param n The value to compute a factorial of.
    @return an int  that is the result of the factorial operation.
*/

int factorial(int n){
    
    // recursive case , for a number n that is not 1
    if(n > 1)     
        return n * factorial(n-1);
    // Base case
    else
        return 1;

}
