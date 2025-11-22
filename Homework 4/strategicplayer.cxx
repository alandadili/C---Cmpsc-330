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

#include "strategicplayer.h"
#include <cstdlib>

int StrategicPlayer::EvaluateLine(const Board& board, int r, int c, char player) 
{
    int score = 0;
    
    // Horizontal line
    if (c % 2 == 1) 
    {
        // Check box above
        if (r >= 2) 
        {
            int sides = 0;
            if (board(r-1, c-1) != '0') sides++;
            if (board(r-1, c+1) != '0') sides++;
            if (board(r-2, c) != '0') sides++;
            if (sides == 3) score += 100; // Complete a box
            else if (sides == 2) score -= 10; // Give opponent opportunity
        }
        // Check box below
        if (r < board.GetDotsInRows() - 2) 
        {
            int sides = 0;
            if (board(r+1, c-1) != '0') sides++;
            if (board(r+1, c+1) != '0') sides++;
            if (board(r+2, c) != '0') sides++;
            if (sides == 3) score += 100;
            else if (sides == 2) score -= 10;
        }
    }
    // Vertical line
    else if (r % 2 == 1) 
    {
        // Check box to the left
        if (c >= 2) 
        {
            int sides = 0;
            if (board(r-1, c-1) != '0') sides++;
            if (board(r+1, c-1) != '0') sides++;
            if (board(r, c-2) != '0') sides++;
            if (sides == 3) score += 100;
            else if (sides == 2) score -= 10;
        }
        // Check box to the right
        if (c < board.GetDotsInCols() - 2) 
        {
            int sides = 0;
            if (board(r-1, c+1) != '0') sides++;
            if (board(r+1, c+1) != '0') sides++;
            if (board(r, c+2) != '0') sides++;
            if (sides == 3) score += 100;
            else if (sides == 2) score -= 10;
        }
    }
    
    return score;
}

void StrategicPlayer::SelectLineLocation(const Board& board, int& r, int& c) 
{
    int max_lines = board.GetDotsInRows() * board.GetDotsInCols();
    int* empty_rows = new int[max_lines];
    int* empty_cols = new int[max_lines];
    
    int count = board.GetAllEmptyLineLocations(empty_rows, empty_cols);
    
    int best_score = -1000;
    int best_idx = 0;
    
    for (int i = 0; i < count; i++) 
    {
        int score = EvaluateLine(board, empty_rows[i], empty_cols[i], player_char);
        if (score > best_score) 
        {
            best_score = score;
            best_idx = i;
        }
    }
    
    r = empty_rows[best_idx];
    c = empty_cols[best_idx];
    
    delete[] empty_rows;
    delete[] empty_cols;
}
