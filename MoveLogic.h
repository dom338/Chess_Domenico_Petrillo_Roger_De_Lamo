#pragma once
#include <vector>
using Board = std::vector<std::vector<char>>;

extern bool gameOver;
extern char winner;  // W = White, B = Black

// General functions
bool Inbounds(int row, int col);
bool IsEmptySquare(char square);
bool IsWhitePiece(char piece);
bool IsBlackPiece(char piece);
void UserToIndexCoordinates(int x, int y, int& row, int& col);
Board CreateBoard();
void PrintBoard(const Board& board);