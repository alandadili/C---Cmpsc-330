//---------------------------------------------------------------------
// Name: Aland Adili
// Email: ava6698@psu.edu
// Class: CMPSC 330
// Program 1
// Due Date: October 03, 2025
//
// Description: This program reads a sequence of characters
// from the keyboard and write the characters in reverse order
// to a file as well as to the monitor
//
// Acknowledgement:
// 1. I discussed with Max Goof how to read a character from the keyboard
// and Max Goof showed me how to use operator<<
// 2. I found a program that shows how to write a character to a file at
// www.blah.com/how-to-write-char-to-file.html
// and used it as a reference for my implementation
//---------------------------------------------------------------------

#include <iostream>

int kaprekar_number(int x); //function prototype


int main()
{
    int x;
    std::cout << "Enter a number to check if it is a Kaprekar number: ";
    std::cin >> x;
    kaprekar_number(x);
    return 0;
}



int kaprekar_number(int x)
{
    bool found = false;
    for (int i = 1; i <= x; ++i) 
    {
        int sq = i * i;
        int num_digits = 0;
        int temp = i;
        while (temp > 0) 
        {
            num_digits++;
            temp /= 10;
        }
        int pow10 = 1;
        for (int j = 0; j < num_digits; ++j) pow10 *= 10;
        int right = sq % pow10;
        int left = sq / pow10;
        if (right + left == i) 
        {
            std::cout << i << std::endl;
            found = true;
        }
    }
    if (!found) 
    {
        std::cerr << "No Kaprekar numbers found for the given input." << std::endl;
    }
    return 0;
}
// add comments