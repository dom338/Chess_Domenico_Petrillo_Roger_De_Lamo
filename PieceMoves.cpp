#include <iostream>
#include <cmath>
#include "PieceMoves.h"

/// <summary>
/// control if the square in a straight line are empty for the selected piece 
/// </summary>
/// <param name="board"></param>
/// is the beard itself
/// <param name="raw1"></param>
/// <param name="col1"></param>
/// <param name="raw2"></param>
/// <param name="col2"></param>
/// <returns></returns>
bool IsThePathClearStraight(const Board& board, int row1, int col1, int row2, int col2) {
    int DirectionRow = (row2 == row1) ? 0 : (row2 > row1 ? 1 : -1);
    int DirectionCol = (col2 == col1) ? 0 : (col2 > col1 ? 1 : -1);
    int row = row1 + DirectionRow;
    int col = col1 + DirectionCol;

    while (row != row2 || col != col2) {
        if (!IsEmptySquare(board[row][col])) return false;
        row += DirectionRow;
        col += DirectionCol;
    }
    return true;
}

/// <summary>
/// control if there are no pices in diagonal trhow the column and the raw
/// </summary>
/// <param name="board"></param>
/// <param name="raw1"></param>
/// <param name="col1"></param>
/// <param name="raw2"></param>
/// <param name="col2"></param>
/// <returns></returns>
bool IsThePathClearDiagonal(const Board& board, int row1, int col1, int row2, int col2) {
    int DirectionRow = (row2 > row1) ? 1 : -1;
    int DirectionCol = (col2 > col1) ? 1 : -1;
    int row = row1 + DirectionRow;
    int col = col1 + DirectionCol;
    while (row != row2 && col != col2) {
        if (!IsEmptySquare(board[row][col])) return false;
        row += DirectionRow; col += DirectionCol;
    }
    return true;
}

// Pawn moves
bool ValidPawnMove(const Board& board, int row1, int col1, int row2, int col2, bool whiteTurn) {
    int Direction = whiteTurn ? -1 : 1;
    int startRow = whiteTurn ? 6 : 1;
    char DestinationSqare = board[row2][col2];

    if (col1 == col2 && row2 == row1 + Direction && IsEmptySquare(DestinationSqare)) return true;
    if (col1 == col2 && row1 == startRow && row2 == row1 + 2 * Direction &&
        IsEmptySquare(board[row1 + Direction][col1]) && IsEmptySquare(DestinationSqare)) return true;
    if ((col2 == col1 + 1 || col2 == col1 - 1) && row2 == row1 + Direction && !IsEmptySquare(DestinationSqare)) {
        if (whiteTurn && IsBlackPiece(DestinationSqare)) return true;
        if (!whiteTurn && IsWhitePiece(DestinationSqare)) return true;
    }
    return false;
}

// Check piece color
bool IsCorrectTurnPiece(char StartingSquare, bool whiteTurn) {
    if (IsEmptySquare(StartingSquare)) return false;
    return whiteTurn ? IsWhitePiece(StartingSquare) : IsBlackPiece(StartingSquare);
}

bool IsCapturingOwnPiece(char StartingSqare, char DestinationSqare) {
    if (IsEmptySquare(DestinationSqare)) return false;
    return (IsWhitePiece(StartingSqare) && IsWhitePiece(DestinationSqare)) ||
        (IsBlackPiece(StartingSqare) && IsBlackPiece(DestinationSqare));
}

// Validate move for any piece
bool ValidMoveForPiece(const Board& board, int row1, int col1, int row2, int col2, bool whiteTurn) {
    if (!Inbounds(row1, col1) || !Inbounds(row2, col2) || (row1 == row2 && col1 == col2)) return false;
    char Piece = board[row1][col1];
    if (!IsCorrectTurnPiece(Piece, whiteTurn)) return false;
    if (IsCapturingOwnPiece(Piece, board[row2][col2])) return false;

    int dRow = row2 - row1;
    int dCol = col2 - col1;

    switch (Piece) {
    case 'P': case 'p': return ValidPawnMove(board, row1, col1, row2, col2, whiteTurn);
    case 'T': case 't': return (row1 == row2 || col1 == col2) && IsThePathClearStraight(board, row1, col1, row2, col2);
    case 'B': case 'b': return std::abs(dRow) == std::abs(dCol) && IsThePathClearDiagonal(board, row1, col1, row2, col2);
    case 'Q': case 'q': return (row1 == row2 || col1 == col2 ? IsThePathClearStraight(board, row1, col1, row2, col2) : IsThePathClearDiagonal(board, row1, col1, row2, col2) && std::abs(dRow) == std::abs(dCol));
    case 'H': case 'h': return (std::abs(dRow) == 2 && std::abs(dCol) == 1) || (std::abs(dRow) == 1 && std::abs(dCol) == 2);
    case 'K': case 'k': return std::abs(dRow) <= 1 && std::abs(dCol) <= 1;
    default: return false;
    }
}

// Promotions and apply move
void PromoteIfNeeded(Board& board, int row, int col) {
    if (board[row][col] == 'P' && row == 0) board[row][col] = 'Q';
    if (board[row][col] == 'p' && row == 7) board[row][col] = 'q';
}

void ApplyMove(Board& board, int row1, int col1, int row2, int col2) {
    char captured = board[row2][col2];
    if (captured == 'K') { std::cout << "Checkmate. Black wins.\n"; gameOver = true; winner = 'B'; }
    else if (captured == 'k') { std::cout << "Checkmate. White wins.\n"; gameOver = true; winner = 'W'; }
    board[row2][col2] = board[row1][col1];
    board[row1][col1] = '*';
    PromoteIfNeeded(board, row2, col2);
}

void WinnerMessage() {
    if (winner == 'W') std::cout << "Checkmate. White wins.\n";
    else if (winner == 'B') std::cout << "Checkmate. Black wins.\n";
}

bool ReadMove(int& x1, int& y1, int& x2, int& y2) {
    if (!(std::cin >> x1)) return false;
    if (x1 == 0) return false;
    if (!(std::cin >> y1 >> x2 >> y2)) return false;
    return true;
}