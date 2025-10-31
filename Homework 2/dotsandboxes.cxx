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

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cctype>
#include <cstdlib> // for std::exit

using namespace std;

// Structure to hold player information
struct Player {
    string name;
    int boxes;
};

// Function prototypes
void readGameLog(const char* filename, int& rows, int& cols, 
                 string*& players, int*& rowMoves, int*& colMoves, 
                 int& moveCount, bool& invalidMove, int& invalidRow, int& invalidCol);
char** allocateBoard(int rows, int cols);
void deallocateBoard(char** board, int rows);
void initializeBoard(char** board, int rows, int cols);
void placeLine(char** board, int rows, int cols, const string& player, 
               int row, int col, Player*& playerList, int& playerCount,
               bool& invalidMove, int& invalidRow, int& invalidCol);
char checkBox(char** board, int boxRow, int boxCol, int rows, int cols);
int countBoxesRecursive(char** board, int rows, int cols, int currentRow, 
                        int currentCol, char playerInitial);
void printBoard(char** board, int rows, int cols);
void printResults(Player* playerList, int playerCount);
int findPlayer(Player* playerList, int playerCount, const string& name);
void sortPlayers(Player* playerList, int playerCount);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <game_file>" << endl;
        return 1;
    }

    int rows, cols;
    string* players = NULL;
    int* rowMoves = NULL;
    int* colMoves = NULL;
    int moveCount = 0;
    bool invalidMove = false;
    int invalidRow = -1, invalidCol = -1;

    // Read game log
    readGameLog(argv[1], rows, cols, players, rowMoves, colMoves, 
                moveCount, invalidMove, invalidRow, invalidCol);

    // Allocate and initialize board
    char** board = allocateBoard(rows, cols);
    initializeBoard(board, rows, cols);

    // Player tracking
    Player* playerList = NULL;
    int playerCount = 0;

    // Place lines and check for boxes
    for (int i = 0; i < moveCount; i++) {
        placeLine(board, rows, cols, players[i], rowMoves[i], colMoves[i],
                  playerList, playerCount, invalidMove, invalidRow, invalidCol);
        if (invalidMove) {
            break;
        }
    }

    // Print the board
    printBoard(board, rows, cols);

    // Print results
    printResults(playerList, playerCount);

    // Deallocate memory
    deallocateBoard(board, rows);
    delete[] players;
    delete[] rowMoves;
    delete[] colMoves;
    delete[] playerList;

    return 0;
}

void readGameLog(const char* filename, int& rows, int& cols,
                 string*& players, int*& rowMoves, int*& colMoves,
                 int& moveCount, bool& invalidMove, int& invalidRow, int& invalidCol) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        std::exit(1);
    }

    file >> rows >> cols;

    // The input provides the number of dots (not character grid size).
    // Convert to character-board dimensions: rows = 2*rows - 1, cols = 2*cols - 1.
    rows = rows * 2 - 1;
    cols = cols * 2 - 1;

    // Allocate temporary arrays (max possible moves)
    int maxMoves = rows * cols;
    players = new string[maxMoves];
    rowMoves = new int[maxMoves];
    colMoves = new int[maxMoves];

    moveCount = 0;
    string playerName;
    while (file >> playerName && playerName != "END") {
        players[moveCount] = playerName;
        file >> rowMoves[moveCount] >> colMoves[moveCount];
        moveCount++;
    }

    file.close();
}

char** allocateBoard(int rows, int cols) {
    char** board = new char*[rows];
    for (int i = 0; i < rows; i++) {
        board[i] = new char[cols];
    }
    return board;
}

void deallocateBoard(char** board, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] board[i];
    }
    delete[] board;
}

void initializeBoard(char** board, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i % 2 == 0 && j % 2 == 0) {
                board[i][j] = '.'; // Dot
            } else {
                board[i][j] = ' '; // Empty space for lines or boxes
            }
        }
    }
}

void placeLine(char** board, int rows, int cols, const string& player,
               int row, int col, Player*& playerList, int& playerCount,
               bool& invalidMove, int& invalidRow, int& invalidCol) {
    // Ensure the player exists in the tracking list (even if they never score a box)
    int pidx = findPlayer(playerList, playerCount, player);
    if (pidx == -1) {
        Player* newList = new Player[playerCount + 1];
        for (int i = 0; i < playerCount; i++) newList[i] = playerList[i];
        newList[playerCount].name = player;
        newList[playerCount].boxes = 0;
        delete[] playerList;
        playerList = newList;
        playerCount++;
    }
    // Check if position is valid
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        invalidMove = true;
        invalidRow = row;
        invalidCol = col;
        return;
    }

    // Check if location is a valid line position
    // Valid line positions are (even, odd) horizontal or (odd, even) vertical.
    // Dots (even, even) and box centers (odd, odd) are invalid.
    bool isDot = (row % 2 == 0 && col % 2 == 0);
    bool isBoxCenter = (row % 2 == 1 && col % 2 == 1);
    if (isDot || isBoxCenter) {
        invalidMove = true;
        invalidRow = row;
        invalidCol = col;
        // Mark the wrong place with 'X' and stop the game immediately.
        board[row][col] = 'X';
        return;
    }

    // Check if the position is already occupied
    if (board[row][col] != ' ') {
        invalidMove = true;
        invalidRow = row;
        invalidCol = col;
        board[row][col] = 'X';
        return;
    }

    // Place the line
    board[row][col] = player[0];

    // Check adjacent boxes
    // Check box above (if this is a horizontal line)
    if (row % 2 == 0 && col % 2 == 1 && row >= 2) {
        char complete = checkBox(board, row - 1, col, rows, cols);
        if (complete != ' ') {
            // Mark the box center with the current player's lowercase initial
            board[row - 1][col] = (char)tolower(player[0]);
            int idx = findPlayer(playerList, playerCount, player);
            if (idx != -1) {
                playerList[idx].boxes++;
            }
        }
    }

    // Check box below (if this is a horizontal line)
    if (row % 2 == 0 && col % 2 == 1 && row < rows - 2) {
        char complete = checkBox(board, row + 1, col, rows, cols);
        if (complete != ' ') {
            board[row + 1][col] = (char)tolower(player[0]);
            int idx = findPlayer(playerList, playerCount, player);
            if (idx != -1) {
                playerList[idx].boxes++;
            }
        }
    }

    // Check box to the left (if this is a vertical line)
    if (row % 2 == 1 && col % 2 == 0 && col >= 2) {
        char complete = checkBox(board, row, col - 1, rows, cols);
        if (complete != ' ') {
            board[row][col - 1] = (char)tolower(player[0]);
            int idx = findPlayer(playerList, playerCount, player);
            if (idx != -1) {
                playerList[idx].boxes++;
            }
        }
    }

    // Check box to the right (if this is a vertical line)
    if (row % 2 == 1 && col % 2 == 0 && col < cols - 2) {
        char complete = checkBox(board, row, col + 1, rows, cols);
        if (complete != ' ') {
            board[row][col + 1] = (char)tolower(player[0]);
            int idx = findPlayer(playerList, playerCount, player);
            if (idx != -1) {
                playerList[idx].boxes++;
            }
        }
    }
}

char checkBox(char** board, int boxRow, int boxCol, int rows, int cols) {
    // Box center is at odd row, odd col
    if (boxRow % 2 != 1 || boxCol % 2 != 1) {
        return ' ';
    }

    // Check if all four sides are filled
    char top = (boxRow >= 1) ? board[boxRow - 1][boxCol] : ' ';
    char bottom = (boxRow < rows - 1) ? board[boxRow + 1][boxCol] : ' ';
    char left = (boxCol >= 1) ? board[boxRow][boxCol - 1] : ' ';
    char right = (boxCol < cols - 1) ? board[boxRow][boxCol + 1] : ' ';

    if (top != ' ' && bottom != ' ' && left != ' ' && right != ' ') {
        // Indicate that the box is complete. Caller will set the owner.
        return '*';
    }

    return ' ';
}

int countBoxesRecursive(char** board, int rows, int cols, int currentRow,
                        int currentCol, char playerInitial) {
    // Base case: out of bounds
    if (currentRow >= rows || currentCol >= cols) {
        return 0;
    }

    int count = 0;

    // Check if current position is a box owned by player
    if (currentRow % 2 == 1 && currentCol % 2 == 1) {
        char cell = board[currentRow][currentCol];
        if (cell == playerInitial || cell == (char)(playerInitial - 32)) {
            count = 1;
        }
    }

    // Recursive case: move to next column
    if (currentCol + 1 < cols) {
        count += countBoxesRecursive(board, rows, cols, currentRow, 
                                      currentCol + 1, playerInitial);
    } else if (currentRow + 1 < rows) {
        // Move to next row
        count += countBoxesRecursive(board, rows, cols, currentRow + 1, 
                                      0, playerInitial);
    }

    return count;
}

void printBoard(char** board, int rows, int cols) {
    // Print column headers
    cout << "  ";
    for (int j = 0; j < cols; j++) {
        cout << (j / 10);
    }
    cout << endl;

    cout << "  ";
    for (int j = 0; j < cols; j++) {
        cout << (j % 10);
    }
    cout << endl;

    // Print rows
    for (int i = 0; i < rows; i++) {
        cout << (i / 10) << (i % 10) << " ";
        for (int j = 0; j < cols; j++) {
            cout << board[i][j];
        }
        cout << endl;
    }
}

void printResults(Player* playerList, int playerCount) {
    // Sort players by name
    sortPlayers(playerList, playerCount);

    // Find max boxes
    int maxBoxes = 0;
    for (int i = 0; i < playerCount; i++) {
        if (playerList[i].boxes > maxBoxes) {
            maxBoxes = playerList[i].boxes;
        }
    }

    // Count winners
    int winnerCount = 0;
    for (int i = 0; i < playerCount; i++) {
        if (playerList[i].boxes == maxBoxes) {
            winnerCount++;
        }
    }

    // Print results
    for (int i = 0; i < playerCount; i++) {
        cout << "Player " << playerList[i].name << " has " 
             << playerList[i].boxes << " box";
        if (playerList[i].boxes != 1) {
            cout << "es";
        }

        if (playerList[i].boxes == maxBoxes) {
            if (winnerCount > 1) {
                cout << " (tie)";
            } else {
                cout << " (win)";
            }
        }
        cout << "." << endl;
    }
}

int findPlayer(Player* playerList, int playerCount, const string& name) {
    for (int i = 0; i < playerCount; i++) {
        if (playerList[i].name == name) {
            return i;
        }
    }
    return -1;
}

void sortPlayers(Player* playerList, int playerCount) {
    // Simple bubble sort by name (lexicographical order)
    for (int i = 0; i < playerCount - 1; i++) {
        for (int j = 0; j < playerCount - i - 1; j++) {
            if (playerList[j].name > playerList[j + 1].name) {
                Player temp = playerList[j];
                playerList[j] = playerList[j + 1];
                playerList[j + 1] = temp;
            }
        }
    }
}