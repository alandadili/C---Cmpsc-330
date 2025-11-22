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

#ifndef BOARD_H
#define BOARD_H

class Board 
{
private:
    int dots_in_rows;
    int dots_in_cols;
    char** board;
    
public:
    Board(int dots_in_rows, int dots_in_cols);
    ~Board();
    
    char& operator()(int row, int col);
    const char& operator()(int row, int col) const;
    
    int GetAllEmptyLineLocations(int* empty_rows, int* empty_cols) const;
    bool IsValidLine(int r, int c) const;
    bool AddLine(int r, int c, char player);
    int CheckBoxesFormed(int r, int c, char player);
    void PrintBoard() const;
    int GetDotsInRows() const { return dots_in_rows; }
    int GetDotsInCols() const { return dots_in_cols; }
};

#endif