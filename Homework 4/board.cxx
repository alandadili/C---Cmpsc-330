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

#include "board.h"
#include <iostream>
using namespace std;

Board::Board(int dots_in_rows, int dots_in_cols) 
    : dots_in_rows(dots_in_rows), dots_in_cols(dots_in_cols) 
    {
    board = new char*[dots_in_rows];
    for (int i = 0; i < dots_in_rows; i++) 
    {
        board[i] = new char[dots_in_cols];
        for (int j = 0; j < dots_in_cols; j++) 
        {
            board[i][j] = '0';
        }
    }
}

Board::~Board() 
{
    for (int i = 0; i < dots_in_rows; i++) 
    {
        delete[] board[i];
    }
    delete[] board;
}

char& Board::operator()(int row, int col) 
{
    return board[row][col];
}

const char& Board::operator()(int row, int col) const 
{
    return board[row][col];
}

int Board::GetAllEmptyLineLocations(int* empty_rows, int* empty_cols) const 
{
    int count = 0;
    for (int i = 0; i < dots_in_rows; i++) 
    {
        for (int j = 0; j < dots_in_cols; j++) 
        {
            if (board[i][j] == '0') 
            {
                empty_rows[count] = i;
                empty_cols[count] = j;
                count++;
            }
        }
    }
    return count;
}

bool Board::IsValidLine(int r, int c) const 
{
    if (r < 0 || r >= dots_in_rows || c < 0 || c >= dots_in_cols) 
    {
        return false;
    }
    
    // Check if it's a valid line position (not a dot position)
    if (r % 2 == 0 && c % 2 == 0) 
    {
        return false; // This is a dot position
    }
    
    return board[r][c] == '0';
}

int Board::CheckBoxesFormed(int r, int c, char player) 
{
    int boxes = 0;
    
    // Horizontal line
    if (c % 2 == 1) 
    {
        // Check box above
        if (r >= 2) 
        {
            if (board[r-1][c-1] == player && board[r-1][c+1] == player &&
                board[r-2][c] == player) 
        {
                board[r-1][c] = player;
                boxes++;
            }
        }
        // Check box below
        if (r < dots_in_rows - 2) {
            if (board[r+1][c-1] == player && board[r+1][c+1] == player &&
                board[r+2][c] == player) {
                board[r+1][c] = player;
                boxes++;
            }
        }
    }
    // Vertical line
    else if (r % 2 == 1) 
    {
        // Check box to the left
        if (c >= 2) 
        {
            if (board[r-1][c-1] == player && board[r+1][c-1] == player &&
                board[r][c-2] == player) 
            {
                board[r][c-1] = player;
                boxes++;
            }
        }
        // Check box to the right
        if (c < dots_in_cols - 2) 
        {
            if (board[r-1][c+1] == player && board[r+1][c+1] == player &&
                board[r][c+2] == player) 
            {
                board[r][c+1] = player;
                boxes++;
            }
        }
    }
    
    return boxes;
}

bool Board::AddLine(int r, int c, char player) 
{
    if (!IsValidLine(r, c)) 
    {
        return false;
    }
    board[r][c] = player;
    return true;
}

void Board::PrintBoard() const 
{
    for (int i = 0; i < dots_in_rows; i++) 
    {
        for (int j = 0; j < dots_in_cols; j++) 
        {
            if (i % 2 == 0 && j % 2 == 0) 
            {
                cout << ".";
            } else if (i % 2 == 0 && j % 2 == 1) 
            {
                if (board[i][j] == '0') cout << " ";
                else cout << "-";
            } else if (i % 2 == 1 && j % 2 == 0) 
            {
                if (board[i][j] == '0') cout << " ";
                else cout << "|";
            } else 
            {
                if (board[i][j] == 'B') cout << "B";
                else if (board[i][j] == 'R') cout << "R";
                else cout << " ";
            }
        }
        cout << endl;
    }
}