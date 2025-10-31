//---------------------------------------------------------------------
// Name: Aland Adili
// Email: ava6698@psu.edu
// Class: CMPSC 330
// Program 2
// Due Date: October 31, 2025
//
// Description: This program reads a dots and boxes game log from a file
// and determines the winner by tracking which player completes each box.
// It uses dynamic memory allocation for the board and recursion for
// checking box completion.
//
// Acknowledgement:
// Consulted with students in Sunlab
// Utilized copilot to help with outputing a text file
// Utilized copilot to help with comments
//---------------------------------------------------------------------

Homework 2 Readme

Windows commands that I used to compile and run the dotsandboxes.cxx and game1.txt files:

1. g++ -ansi -pedantic -std=c++14 -Wall ".\dotsandboxes.cxx" -o ".\dotsandboxes.exe" (Compile)
2. .\dotsandboxes.exe ".\game1.txt" > ".\game_out.txt" (Run and write output to file)
3. Get-Content ".\game_out.txt" (Check output)

Linux commands that I used to compile and run the dotsandboxes.cxx and game1.txt files (Sunlab):

1. g++ -ansi -pedantic -std=c++14 -Wall dotsandboxes.cxx -o dotsandboxes (Compile)
2. $ ./dotsandboxes game1.txt (> out.txt to have an output txt file)
