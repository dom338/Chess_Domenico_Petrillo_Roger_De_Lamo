#pragma once
#include <vector>
using Board = std::vector<std::vector<char>>;
extern bool gameOver;

// General functions
bool Inbounds(int row, int col);
bool IsEmptySquare(char square);
bool IsWhitePiece(char piece);
bool IsBlackPiece(char piece);
void UserToIndexCoordinates(int x, int y, int& row, int& col);
Board CreateBoard();
void PrintBoard(const Board& board);

//Check and checkmate functions
void FindKing(const Board& board, bool whiteKing, int& kingRow, int& kingCol);
bool SquareUnderAttack(const Board& board, int row, int col, bool attackedByWhite);
bool KingCheck(const Board& board, bool whiteKing);
bool AnyMove(Board& board, bool whiteTurn);
bool Checkmate(Board& board, bool whiteTurn);