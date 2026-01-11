#include <iostream>
#include "MoveLogic.h"

bool gameOver = false;
char winner = ' ';

/// <summary>
/// check if the given position is inside the chessboard
/// </summary>
/// <param name="row"></param>
/// row is the row index
/// <param name="col"></param>
/// col is the column index
/// <returns></returns>
bool Inbounds(int row, int col) {
    return row >= 0 && row < 8 && col >= 0 && col < 8;
}

/// <summary>
/// check if the given square is empty
/// </summary>
/// <param name="square"></param>
/// square is the character representing the empty square
/// <returns></returns>
bool IsEmptySquare(char square) {
    return square == '*';
}

// Check piece color
bool IsWhitePiece(char piece) { return piece >= 'A' && piece <= 'Z'; }
bool IsBlackPiece(char piece) { return piece >= 'a' && piece <= 'z'; }

/// <summary>
/// convert user coordinates to index coordinates
/// </summary>
/// <param name="x"></param>
/// x is the user x coordinate for the column
/// <param name="y"></param>
/// y is the user y coordinate for the row
/// <param name="row"></param>
/// row is the index row
/// <param name="col"></param>
/// col is the index column
void UserToIndexCoordinates(int x, int y, int& row, int& col) {
    row = 8 - y;
    col = x - 1;
}

/// <summary>
/// create and return the initial chessboard
/// </summary>
/// <returns></returns>
Board CreateBoard() {
    Board board(8, std::vector<char>(8, '*'));
    board[0] = { 't','h','b','q','k','b','h','t' };
    board[1] = { 'p','p','p','p','p','p','p','p' };
    board[6] = { 'P','P','P','P','P','P','P','P' };
    board[7] = { 'T','H','B','Q','K','B','H','T' };
    return board;
}

/// <summary>
/// print the chessboard
/// </summary>
/// <param name="board"></param>
/// board is the chessboard to print
void PrintBoard(const Board& board) {
    std::cout << "\n  1 2 3 4 5 6 7 8\n";
    for (int row = 0; row < 8; ++row) {
        std::cout << 8 - row << ' ';
        for (int col = 0; col < 8; ++col)
            std::cout << board[row][col] << ' ';
        std::cout << 8 - row << '\n';
    }
    std::cout << "  1 2 3 4 5 6 7 8\n";
}