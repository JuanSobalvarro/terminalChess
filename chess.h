#ifndef CHESS_H
#define CHESS_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "terminalcolors.h"

typedef struct BoardSymbol
{
    char symbol;
    bool player; // 0 is white 1 is black
} BoardSymbol;

typedef struct Position
{
    int row;
    int column;
} Position;

typedef struct Piece
{
    struct Position *pos;
    char symbol;
} Piece;

typedef struct ChessBoard
{
    RGB whiteColor;
    RGB blackColor;
    RGB whiteCellsColor;
    RGB blackCellsColor;
    struct Piece** wPieces;
    struct Piece** bPieces;
    int wSize;
    int bSize;
    struct BoardSymbol board[8][8];
    bool turn; // 0 is white 1 is black
} ChessBoard;

void printChess(struct ChessBoard* cb);
void __populateChess(struct ChessBoard* cb);

struct ChessBoard* createChess(RGB whitePlayerColor, RGB blackPlayerColor, RGB whiteCellsColor, RGB blackCellsColor);

void cleanChess(struct ChessBoard* cb);

#endif // CHESS_H