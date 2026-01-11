// Chess_Domenico_Petrillo_Roger_De_Lamo.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include <iostream>
#include <vector>
#include <cctype>
#include <cmath>
#include "Header.h"

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

bool IsWhitePiece(char piece) {
    if (piece >= 'A' && piece <= 'Z')
    {
        return true;
    }
    else
    {
		return false;
    }
}

bool IsBlackPiece(char piece) 
{
    if (piece >= 'a' && piece <= 'z')
    {
        return true;
    }
    else
    {
        return false;
    }
}

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
Board CreateBoard() 
{
    Board board(8, std::vector<char>(8, '*'));
    // Place black pieces
    board[0] = { 't', 'h', 'b', 'q', 'k', 'b', 'h', 't' };
    board[1] = { 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p' };
    // Place white pieces
    board[6] = { 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P' };
    board[7] = { 'T', 'H', 'B', 'Q', 'K', 'B', 'H', 'T' };
    return board;
}


/// <summary>
/// print the chessboard
/// </summary>
/// <param name="board"></param>
/// board is the chessboard to print
void PrintBoard(const Board& board) 
{
    std::cout << "\n  1 2 3 4 5 6 7 8\n";
    for (int row = 0; row < 8; ++row) 
    {
        std::cout << 8 - row << ' ';
        for (int col = 0; col < 8; ++col) 
        {
            std::cout << board[row][col] << ' ';
        }
        std::cout << 8 - row << '\n';
    }
    std::cout << "  1 2 3 4 5 6 7 8\n";
}


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
bool IsThePathClearStraight(const Board& board, int raw1, int col1, int raw2, int col2)
{
    int DirectionRow = (raw2 == raw1) ? 0 : (raw2 > raw1 ? 1 : -1);
    int DirectionCol = (col2 == col1) ? 0 : (col2 > col1 ? 1 : -1);

    int raw = raw1 + DirectionRow;
    int col = col1 + DirectionCol;

    while (raw != raw2 || col != col2)
    {
        if (!IsEmptySquare(board[raw][col])) return false;
        raw = raw + DirectionRow;
        col = col + DirectionCol;
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

bool IsThePathClearDiagonal(const Board& board, int raw1, int col1, int raw2, int col2)
{
    int DirectionRaw = (raw2 > raw1) ? 1 : -1;
    int DirectionCol = (col2 > col1) ? 1 : -1;

    int raw = raw1 + DirectionRaw;
    int col = col1 + DirectionCol;

    while (raw != raw2 && col != col2)
    {
        if (!IsEmptySquare(board[raw][col])) return false;
		else
        {
            raw = raw + DirectionRaw;
            col = col + DirectionCol;

        }
    }
    return true;
}

bool ValidPawnMove(const Board& board, int raw1, int col1, int raw2, int col2, bool whiteTurn)
{
    int Direction = whiteTurn ? -1 : 1;
    int startRaw = whiteTurn ? 6 : 1;

    char DestinationSqare = board[raw2][col2];

    if (col1 == col2 && raw2 == raw1 + Direction && IsEmptySquare(DestinationSqare))
    {
        return true;
    }
    if (col1 == col2 && raw1 == startRaw && raw2 == raw1 + 2 * Direction)
    {
		int MiddleRaw = raw1 + Direction;
        if (IsEmptySquare(board[MiddleRaw][col1]) && IsEmptySquare(DestinationSqare))
        {
            return true;
        }
    }
    if ((col2 == col1 +1 || col2 == col1 -1) && raw2 == raw1 + Direction && !IsEmptySquare(DestinationSqare))
    {
        if (whiteTurn && IsBlackPiece(DestinationSqare)) return true;
		if (!whiteTurn && IsWhitePiece(DestinationSqare)) return true;
    }
	return false;
}

bool IsCorrectTurnPiece(char StartingSquare, bool whiteTurn)
{
    if (IsEmptySquare(StartingSquare))
    {
        return false;
    }
    if (whiteTurn)
    {
		return IsWhitePiece(StartingSquare);
    }
    else
    {
        return IsBlackPiece(StartingSquare);
    }
}

bool IsCapturingOwnPiece(char StartingSqare, char DestinationSqare)
{
    if (IsEmptySquare(DestinationSqare))
    {
        return false;
    }
    if (IsWhitePiece(StartingSqare) && IsWhitePiece(DestinationSqare))
    {
        return true;
    }
    if (IsBlackPiece(StartingSqare) && IsBlackPiece(DestinationSqare))
    {
        return true;
	}
	return false;
}

bool ValidMouveForPiece(const Board& board, int raw1, int col1, int raw2, int col2, bool whiteTurn)
{
    if (!Inbounds(raw1,col1) || !Inbounds(raw2,col2))
    {
        return false;
    }
    if (raw1 == raw2 && col1 == col2)
    {
        return false;

    }
    char StartingSqare = board[raw1][col1];
    char DestinationSqare = board[raw2][col2];

    if (!IsCorrectTurnPiece(StartingSqare, whiteTurn))
    {
        return false;
    }
    if (IsCapturingOwnPiece(StartingSqare, DestinationSqare))
    {
        return false;
    }

    char Piece = StartingSqare;
    int DirectionRaw = raw2 - raw1;
    int DirectionCol = col2 - col1;

    switch (Piece)
    {
    case 'P': 
    case 'p':
        // Pawn
        return ValidPawnMove(board, raw1, col1, raw2, col2, whiteTurn);
        break;

    case 'T':
    case 't':
        // Rock
        if (raw1 == raw2 || col1 == col2)
            return IsThePathClearStraight(board, raw1, col1, raw2, col2);
        return false;
        break;

    case 'B':
    case 'b':
        // Bishop
        if (std::abs(raw2 - raw1) == std::abs(col2 - col1))
            return IsThePathClearDiagonal(board, raw1, col1, raw2, col2);
        return false;
        break;

    case 'Q':
    case 'q':
        // Queen
        if (raw1 == raw2 || col1 == col2)
            return IsThePathClearStraight(board, raw1, col1, raw2, col2);

 
        if (std::abs(raw2 - raw1) == std::abs(col2 - col1))
            return IsThePathClearDiagonal(board, raw1, col1, raw2, col2);

        return false;
        break;

    case 'H':
    case 'h':
        // Horse

        if ((raw2 == raw1 + 2 || raw2 == raw1 - 2) &&
            (col2 == col1 + 1 || col2 == col1 - 1))
            return true;

        if ((raw2 == raw1 + 1 || raw2 == raw1 - 1) &&
            (col2 == col1 + 2 || col2 == col1 - 2))
            return true;

        return false;

        break;

    case 'K':
    case 'k':
        // King
        if ((raw2 == raw1 || raw2 == raw1 + 1 || raw2 == raw1 - 1) &&
            (col2 == col1 || col2 == col1 + 1 || col2 == col1 - 1))
            return true;

        return false;
        break;

    default: return false;
    }

}

void PromoteIfNeeded(Board& board, int raw, int col)
{
    if (board[raw][col] == 'P' && raw == 0)
    {
        board[raw][col] = 'Q';

    }
    if (board[raw][col] == 'p' && raw == 7)
    {
        board[raw][col] == 'q';
    }
}

void ApplayMove(Board& board, int raw1, int col1, int raw2, int col2)
{
    board[raw2][col2] = board[raw1][col1];
    board[raw1][col1] = '*';
    PromoteIfNeeded(board, raw2, col2);
}

bool ReadMove(int& x1, int& y1, int& x2, int& y2)
{
    if (!(std::cin >> x1)) return false;
    if (x1 == 0) return false;
    if (!(std::cin >> y1 >> x2 >> y2)) return false;
    return true;
}



int main()
{
    std::cout << "Hello welcome to chess!!\n";
	Board chessboard = CreateBoard();
    bool whiteTurn = true;
    int x1, y1, x2, y2;
    int raw1, col1, raw2, col2;

	std::cout << "To make a move enter the coordinates in the format x1 y1 x2 y2\n";
	std::cout << "Where (x1,y1) are the coordinates of the piece to move and (x2,y2) are the destination coordinates\n";
	std::cout << "To exit the game enter 0\n";

    while (gameOver != true)
    {
        PrintBoard(chessboard);
        if (whiteTurn)
        {
            std::cout << "White's turn\n";
        }
        else
        {
            std::cout << "Black's turn\n";
        }

        if (!ReadMove(x1,y1,x2,y2))
        {
            break;
        }

		UserToIndexCoordinates(x1,y1, raw1, col1);
        UserToIndexCoordinates(x2,y2, raw2, col2);
        
        if (!Inbounds(raw1, col1) || !Inbounds (raw2, col2))
        {
            std::cout << "invalid move, please try again";
			continue;
        }
        if (!ValidMouveForPiece(chessboard, raw1, col1, raw2, col2, whiteTurn))
        {
            std::cout << "invalid move, please try again\n";
            continue;
		}
        ApplayMove(chessboard, raw1, col1, raw2, col2);
		whiteTurn = !whiteTurn;
    }
    
}

// Per eseguire il programma: CTRL+F5 oppure Debug > Avvia senza eseguire debug
// Per eseguire il debug del programma: F5 oppure Debug > Avvia debug

// Suggerimenti per iniziare: 
//   1. Usare la finestra Esplora soluzioni per aggiungere/gestire i file
//   2. Usare la finestra Team Explorer per connettersi al controllo del codice sorgente
//   3. Usare la finestra di output per visualizzare l'output di compilazione e altri messaggi
//   4. Usare la finestra Elenco errori per visualizzare gli errori
//   5. Passare a Progetto > Aggiungi nuovo elemento per creare nuovi file di codice oppure a Progetto > Aggiungi elemento esistente per aggiungere file di codice esistenti al progetto
//   6. Per aprire di nuovo questo progetto in futuro, passare a File > Apri > Progetto e selezionare il file con estensione sln
