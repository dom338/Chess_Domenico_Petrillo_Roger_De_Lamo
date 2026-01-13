#include <iostream>
#include "MoveLogic.h"
#include "PieceMoves.h" // to use ValidMoveForPiece

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

//Find the king position
void FindKing(const Board& board, bool whiteTurn, int& kingX, int& kingY) {
    char kingChar = whiteTurn ? 'K' : 'k';
    kingX = -1;
    kingY = -1;
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            if (board[y][x] == kingChar) {
                kingX = x;
                kingY = y;
                return;
            }
        }
    }
}

//Check if a square is under attack by opponent pieces
// This variable setup was assisted by AI
bool SquareUnderAttack(const Board& board, int targetX, int targetY, bool byWhite) {
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            char piece = board[y][x];
            if (IsEmptySquare(piece)) continue;
            if (byWhite && !IsWhitePiece(piece)) continue;
            if (!byWhite && !IsBlackPiece(piece)) continue;

            if (ValidMoveForPiece(board, y, x, targetY, targetX, byWhite)) return true;
        }
    }
    return false;
}

//Check if the king is in check
bool KingCheck(const Board& board, bool whiteTurn) {
    int kingX, kingY;
    FindKing(board, whiteTurn, kingX, kingY);
    if (kingX == -1) return false;
    return SquareUnderAttack(board, kingX, kingY, !whiteTurn);
}

//Check if there is any valid move for the current player
bool AnyMove(Board& board, bool whiteTurn) {
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            char piece = board[y][x];
            if (IsEmptySquare(piece)) continue;
            if (whiteTurn && !IsWhitePiece(piece)) continue;
            if (!whiteTurn && !IsBlackPiece(piece)) continue;

            for (int ty = 0; ty < 8; ++ty) {
                for (int tx = 0; tx < 8; ++tx) {
                    if (ValidMoveForPiece(board, y, x, ty, tx, whiteTurn)) {
                        Board tempBoard = board;
                        char captured = tempBoard[ty][tx];
                        tempBoard[ty][tx] = tempBoard[y][x];
                        tempBoard[y][x] = '*';

                        // If king is not in check after move, it's legal
                        if (!KingCheck(tempBoard, whiteTurn)) return true;
                    }
                }
            }
        }
    }
    return false;
}

//Check for checkmate and update winner
bool Checkmate(Board& board, bool whiteTurn) {
    if (KingCheck(board, whiteTurn)) {
        if (!AnyMove(board, whiteTurn)) {
            gameOver = true;
            std::cout << "Checkmate! " << (whiteTurn ? "Black" : "White") << " wins!\n";
        }
        else {
            std::cout << (whiteTurn ? "White" : "Black") << " is in check!\n";
        }
    }
    return gameOver;
}