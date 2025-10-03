//---------------------------------------------------------------------
// Name: Aland Adili
// Email: ava6698@psu.edu
// Class: CMPSC 330
// Program 1
// Due Date: October 03, 2025
//
// Description: writes a program that reads in a positive integer 1 from the standard input (std::cin) 
// and writes to the standard output (std::cout) all Kaprekar numbers less than or equal to 1, in increasing order.
//
// Acknowledgement:
// Recieved help from student to compile in SunLab
//---------------------------------------------------------------------

#include <iostream>

int kaprekar_number(int x); //function prototype


int main()
{
    int x; // Variable to store user input
    std::cout << "Enter a number to check if it is a Kaprekar number: "; // Prompt user
    std::cin >> x; // Read input
    kaprekar_number(x); // Call function to find and print Kaprekar numbers
    return 0; // End program
}



int kaprekar_number(int x)
{
    bool found = false; // Track if any Kaprekar numbers are found
    // Loop through all numbers from 1 to x
    for (int i = 1; i <= x; ++i) 
    {
        int sq = i * i; // Square the current number
        int num_digits = 0; // Count digits in the current number
        int temp = i;
        while (temp > 0) 
        {
            num_digits++;
            temp /= 10;
        }
        int pow10 = 1; // Calculate 10^num_digits
        for (int j = 0; j < num_digits; ++j) pow10 *= 10;
        int right = sq % pow10; // Get rightmost digits
        int left = sq / pow10; // Get leftmost digits
        // Check Kaprekar condition
        if (right + left == i) 
        {
            std::cout << i << std::endl; // Print Kaprekar number
            found = true;
        }
    }
    // If no Kaprekar numbers found, print error message
    if (!found) 
    {
        std::cerr << "No Kaprekar numbers found for the given input." << std::endl;
    }
    return 0; // End function
}