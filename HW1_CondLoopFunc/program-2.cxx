//---------------------------------------------------------------------
// Name: Aland Adili
// Email: ava6698@psu.edu
// Class: CMPSC 330
// Program 2
// Due Date: October 03, 2025
//
// Description: This program reads a positive integer from input and
// prints all palindromic primes less than or equal to that integer.
// The output is formatted with 5 numbers per line, separated by two
// spaces. A palindromic prime is a prime number that is also a
// palindrome.
//
// Acknowledgement:
// None
//---------------------------------------------------------------------

#include <iostream>
#include <cmath>
#include <string>
using namespace std;

// check if prime
bool prime(unsigned long long a) 
{
    if (a < 2) return false;
    if (a == 2) return true;
    if (a % 2 == 0) return false;
    for (unsigned long long b = 3; b <= sqrt(a); b += 2) 
    {
        if (a % b == 0) return false;
    }
    return true;
}

// check if palindrome
bool pal(unsigned long long a) 
{
    string b = to_string(a);
    string c = string(b.rbegin(), b.rend());
    return b == c;
}

int main() 
{
    unsigned long long a;
    std::cout << "Enter a positive integer to check if it is a palindromic prime: ";
    std::cin >> a;

    int b = 0; // counter for numbers in current line
    for (unsigned long long c = 2; c <= a; c++) 
    {
        if (prime(c) && pal(c)) 
        {
            cout << c;
            b++;
            if (b % 5 == 0) 
            {
                cout << endl; // after 5 numbers, new line
            } else 
            {
                cout << "  "; // two spaces
            }
        }
    }
    if (b % 5 != 0) cout << endl; // finish last line properly

    return 0;
}
