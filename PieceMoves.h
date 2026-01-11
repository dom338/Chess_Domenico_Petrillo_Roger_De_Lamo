#pragma once
#include "MoveLogic.h"

// Path checks
bool IsThePathClearStraight(const Board& board, int row1, int col1, int row2, int col2);
bool IsThePathClearDiagonal(const Board& board, int row1, int col1, int row2, int col2);

// Piece move validation
bool ValidPawnMove(const Board& board, int row1, int col1, int row2, int col2, bool whiteTurn);
bool IsCorrectTurnPiece(char StartingSquare, bool whiteTurn);
bool IsCapturingOwnPiece(char StartingSqare, char DestinationSqare);
bool ValidMoveForPiece(const Board& board, int row1, int col1, int row2, int col2, bool whiteTurn);

// Apply promotions and movements
void PromoteIfNeeded(Board& board, int row, int col);
void ApplyMove(Board& board, int row1, int col1, int row2, int col2);
void WinnerMessage();
bool ReadMove(int& x1, int& y1, int& x2, int& y2);
