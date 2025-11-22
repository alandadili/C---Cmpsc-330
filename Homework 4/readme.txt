//---------------------------------------------------------------------
// Name: Aland Adili
// Email: ava6698@psu.edu
// Class: CMPSC 330
// Homework: 4
// Due Date: November 21, 2025
//
// Description: This program implements a two-player Dots and Boxes game. 
// It reads game settings from standard input, 
// including the board size and two players' names and play types
// (either "random" or "strategic").
//
// Acknowledgement:
// 1. Consulted with students in Sunlab
// 2. Utilized copilot to help with assisting with directory to compile and run the exe file 
// 3. Utilized copilot to help with comments
// 4. Utilized copilot to help with indentation
// 5. Utilized copilot to help with files not being accessed properly
// 6. Utilized stack overflow to understand why it wasnt compiling/creating an exe file
// 7. Researched on stack overflow to see if the following homework would work before compling in the Sunlab
// 7. Worked by myself for the entirety off the Homework 4 assignment
//---------------------------------------------------------------------

Homework 4 Readme

IMPORTANT!
USE GAMEPLAY AS THE MAIN FILE

1. Windows commands that I used to create the gameplay.exe file and run the Dots and Boxes game:
g++ -std=c++14 -Wall board.cxx randomplayer.cxx strategicplayer.cxx gameplay.cxx -o dotsandboxes.exe

2. Test File Runs
dotsandboxes.exe < fourbyfour_2player_0.txt
dotsandboxes.exe < fourbyfour_2player_2.txt
dotsandboxes.exe < tenbyten_2player_0.txt
dotsandboxes.exe < twentybytwenty_2player_2.txt

3. If you want to save output to a file, you can use the following command:
dotsandboxes.exe < fourbyfour_2player_0.txt > output1.txt

4. Linux commands that I used to create the gameplay.exe file and run the Dots and Boxes game (Sunlab):
$ g++ -ansi -pedantic -std=c++14 -Wall board.cxx randomplayer.cxx strategicplayer.cxx gameplay.cxx -o dotsandboxes

5. Running using Linux I used 
$ ./dotsandboxes < input1.txt

Final Remarks:

I removed the test files and exe per usual. Even though it was not clearly stated
I have also packaged all the content into a single CS330_Fall25_HW4_dotsboxes_match zip file
