//Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
#include <iostream>
#include "MoveLogic.h"
#include "PieceMoves.h"

int main() {
    std::cout << "Welcome to chess!!\n";
    Board chessboard = CreateBoard();
    bool whiteTurn = true;
    int x1, y1, x2, y2, row1, col1, row2, col2;

    std::cout << "HOW TO PLAY:\n";
    std::cout << "- Enter your move using four numbers: x1 y1 x2 y2\n";
    std::cout << "- (x1, y1) is the piece you want to move\n";
    std::cout << "- (x2, y2) is the destination square\n";
    std::cout << "- Columns go from 1 to 8 (left to right)\n";
    std::cout << "- Rows go from 1 to 8 (bottom to top)\n";
    std::cout << "- Example: 5 2 5 4 (move pawn from e2 to e4)\n\n";

    std::cout << "Enter 0 at any time to exit the game.\n\n";

    while (!gameOver) {
        PrintBoard(chessboard);
        std::cout << (whiteTurn ? "White's turn\n" : "Black's turn\n");

        if (!ReadMove(x1, y1, x2, y2)) break;

        UserToIndexCoordinates(x1, y1, row1, col1);
        UserToIndexCoordinates(x2, y2, row2, col2);

        if (!Inbounds(row1, col1) || !Inbounds(row2, col2)) {
            std::cout << "Invalid move, try again\n"; continue;
        }
        if (!ValidMoveForPiece(chessboard, row1, col1, row2, col2, whiteTurn)) {
            std::cout << "Invalid move, try again\n"; continue;
        }

        ApplyMove(chessboard, row1, col1, row2, col2);
        Checkmate(chessboard, !whiteTurn);

        if (!gameOver)
            whiteTurn = !whiteTurn; // switch turn only if game continues
    }

    WinnerMessage();
    return 0;
}
// To run the program: Press CTRL+F5 or go to Debug > Start Without Debugging
// To debug the program: Press F5 or go to Debug > Start Debugging

// Getting started tips: 
//   1. Use the Solution Explorer to add or manage project files
//   2. Use Team Explorer to connect to source control if needed
//   3. Check the Output window to view compilation messages and program output
//   4. Use the Error List window to quickly locate errors
//   5. To add a new file, go to Project > Add New Item, or add an existing file via Project > Add Existing Item
//   6. To reopen this project in the future, go to File > Open > Project and select the .sln file