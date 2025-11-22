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

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "board.h"
#include "randomplayer.h"
#include "strategicplayer.h"

using namespace std;

int main() 
{
    srand(time(0));
    
    int dots_rows, dots_cols;
    cin >> dots_rows >> dots_cols;
    
    char name_a, name_b;
    string type_a, type_b;
    
    cin >> name_a >> type_a;
    cin >> name_b >> type_b;
    
    // Convert to actual board size (dots to grid)
    int board_rows = dots_rows * 2 - 1;
    int board_cols = dots_cols * 2 - 1;
    
    Board game_board(board_rows, board_cols);
    
    RandomPlayer* rand_a = nullptr;
    RandomPlayer* rand_b = nullptr;
    StrategicPlayer* strat_a = nullptr;
    StrategicPlayer* strat_b = nullptr;
    
    if (type_a == "Random") 
    {
        rand_a = new RandomPlayer(name_a);
    } else 
    {
        strat_a = new StrategicPlayer(name_a);
    }
    
    if (type_b == "Random") 
    {
        rand_b = new RandomPlayer(name_b);
    } else 
    {
        strat_b = new StrategicPlayer(name_b);
    }
    
    int boxes_a = 0, boxes_b = 0;
    bool player_a_turn = true;
    
    cout << dots_rows << " " << dots_cols << endl;
    
    while (true) 
    {
        int max_lines = board_rows * board_cols;
        int* empty_rows = new int[max_lines];
        int* empty_cols = new int[max_lines];
        int count = game_board.GetAllEmptyLineLocations(empty_rows, empty_cols);
        delete[] empty_rows;
        delete[] empty_cols;
        
        if (count == 0) break;
        
        int r, c;
        char current_player;
        
        if (player_a_turn) {
            current_player = name_a;
            if (rand_a) 
            {
                rand_a->SelectLineLocation(game_board, r, c);
            } else 
            {
                strat_a->SelectLineLocation(game_board, r, c);
            }
        } else 
        {
            current_player = name_b;
            if (rand_b) 
            {
                rand_b->SelectLineLocation(game_board, r, c);
            } else 
            {
                strat_b->SelectLineLocation(game_board, r, c);
            }
        }
        
        game_board.AddLine(r, c, current_player);
        
        cout << current_player << " " << r << " " << c << endl;
        
        int boxes_formed = game_board.CheckBoxesFormed(r, c, current_player);
        
        if (player_a_turn) 
        {
            boxes_a += boxes_formed;
        } else 
        {
            boxes_b += boxes_formed;
        }
        
        if (boxes_formed == 0) 
        {
            player_a_turn = !player_a_turn;
        }
    }
    
    cout << "END" << endl << endl;
    game_board.PrintBoard();
    
    cout << "Player " << name_a << " has " << boxes_a << " boxes";
    if (boxes_a > boxes_b) 
    {
        cout << " (win)." << endl;
    } else if (boxes_a == boxes_b) 
    {
        cout << "." << endl << "It's a tie." << endl;
    } else 
    {
        cout << "." << endl;
    }
    
    if (boxes_a <= boxes_b) 
    {
        cout << "Player " << name_b << " has " << boxes_b << " boxes";
        if (boxes_b > boxes_a) 
        {
            cout << " (win)." << endl;
        } else 
        {
            cout << "." << endl;
        }
    }
    
    delete rand_a;
    delete rand_b;
    delete strat_a;
    delete strat_b;
    
    return 0;
}