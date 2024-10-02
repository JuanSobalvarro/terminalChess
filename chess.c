#include "chess.h"

// King, Queen, Rook, Bishop, knight, Pawn
char SYMBOL_KING = 'K';
char SYMBOL_QUEEN = 'Q';
char SYMBOL_ROOK = 'R';
char SYMBOL_BISHOP = 'B';
char SYMBOL_KNIGHT = 'C';
char SYMBOL_PAWN = 'P';

char CHESS_COLUMNS[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'e'};

void printChess(ChessBoard* cb)
{
    printf("===========\n");
    for (int i = 0; i < 8; i++)
    {
        printf("%d|", 8-i);
        for (int j = 0; j < 8; j++)
        {
            // printf("a");
            if ((i+j)%2)
            {
                backgroundColor(cb->blackCellsColor);
            }
            else
            {
                backgroundColor(cb->whiteCellsColor);
            }
            BoardSymbol bs = cb->board[7 - i][j];
            if (!bs.player)
            {
                textColor(cb->whiteColor);
            }
            else
            {
                textColor(cb->blackColor);
            }
            printf("%c", bs.symbol);
            resetColor();
        }
        printf("|\n");
    }
    printf("-----------\n  ");
    for (int i = 0; i < 8; i++)
    {
        printf("%c", CHESS_COLUMNS[i]);
    }
    printf("\n===========\n");
}

// Given pieces present in our chess board we populate its positions with its symbol
void __populateBoardFromPieces(ChessBoard* cb)
{
    // Populate white pieces
    for (int i = 0; i < cb->wSize; i++)
    {
        Piece* p = cb->wPieces[i];
        Position* pos = p->pos;
        BoardSymbol bs = {p->symbol, 0};
        cb->board[pos->row][pos->column] = bs;
    }
    // Populate black pieces
    for (int i = 0; i < cb->bSize; i++)
    {
        Piece* p = cb->bPieces[i];
        Position* pos = p->pos;
        BoardSymbol bs = {p->symbol, 1};
        cb->board[pos->row][pos->column] = bs;
    }
}

void __populateChess(ChessBoard* cb)
{
    // Populates 0 to empty cells
    // First iterate through rows
    for (int i = 2; i < 6; i++)
    {
        // Then iterate through columns
        for (int j = 0; j < 8; j++)
        {
            BoardSymbol bs = {' ', 0};
            cb->board[i][j] = bs;
        }
    }

    __populateBoardFromPieces(cb);
}

Piece* __createPiece(char symbol, int row, int column)
{
    Piece* p = malloc(sizeof(Piece));

    if (!p)
    {
        printf("Couldnt allocate memory for pawn");
        return NULL;
    }
    
    p->pos = malloc(sizeof(Position));

    p->pos->row = row;
    p->pos->column = column;
    p->symbol = symbol;

    printf("Piece created: %c at %d %c\n", p->symbol, p->pos->row, CHESS_COLUMNS[p->pos->column]);

    return p;
}

void __createDefaultWhitePieces(Piece** pieces)
{
    printf("Creating white pieces\n");
    // Create pawns
    for (int i = 0; i < 8; i++)
    {
        Piece* pawn = __createPiece(SYMBOL_PAWN, 1, i);
        pieces[i] = pawn;
    }
    printf("Pawns created\n");

    // Populate others
    int currentPos = 8;

    // for (int i = 0; i < 2; i++)
    // {
    //     pieces[currentPos++] = __createPiece('R', 0, 0 + 7 * i);
    //     pieces[currentPos++] = __createPiece('k', 0, 1 + 5 * i);
    //     pieces[currentPos++] = __createPiece('B', 0, 2 + 4 * i);
    // }
    
    // rooks
    pieces[currentPos++] = __createPiece(SYMBOL_ROOK, 0, 0);
    pieces[currentPos++] = __createPiece(SYMBOL_ROOK, 0, 7);
    
    // knights
    pieces[currentPos++] = __createPiece(SYMBOL_KNIGHT, 0, 1);
    pieces[currentPos++] = __createPiece(SYMBOL_KNIGHT, 0, 6);

    // bishops
    pieces[currentPos++] = __createPiece(SYMBOL_BISHOP, 0, 2);
    pieces[currentPos++] = __createPiece(SYMBOL_BISHOP, 0, 5);

    // King and queen
    pieces[currentPos++] = __createPiece(SYMBOL_QUEEN, 0, 3);
    pieces[currentPos++] = __createPiece(SYMBOL_KING, 0, 4);

    printf("White pieces successfully created\n");
}

void __createDefaultBlackPieces(Piece** pieces)
{
    printf("Creating black pieces\n");
    // Create pawns
    for (int i = 0; i < 8; i++)
    {
        Piece* pawn = __createPiece('P', 6, i);
        pieces[i] = pawn;
    }
    printf("Pawns created\n");

    // Populate others
    int currentPos = 8;
    
    // rooks
    pieces[currentPos++] = __createPiece(SYMBOL_ROOK, 7, 0);
    pieces[currentPos++] = __createPiece(SYMBOL_ROOK, 7, 7);
    
    // knights
    pieces[currentPos++] = __createPiece(SYMBOL_KNIGHT, 7, 1);
    pieces[currentPos++] = __createPiece(SYMBOL_KNIGHT, 7, 6);

    // bishops
    pieces[currentPos++] = __createPiece(SYMBOL_BISHOP, 7, 2);
    pieces[currentPos++] = __createPiece(SYMBOL_BISHOP, 7, 5);

    // King and queen
    pieces[currentPos++] = __createPiece(SYMBOL_KING, 7, 3);
    pieces[currentPos++] = __createPiece(SYMBOL_QUEEN, 7, 4);

    printf("Black pieces successfully created\n");
}

ChessBoard* createChess(RGB whitePlayerColor, RGB blackPlayerColor, RGB whiteCellsColor, RGB blackCellsColor)
{
    ChessBoard* cb = malloc(sizeof(ChessBoard));

    cb->whiteColor = whitePlayerColor;
    cb->blackColor = blackPlayerColor;
    cb->whiteCellsColor = whiteCellsColor;
    cb->blackCellsColor = blackCellsColor;
    cb->wSize = 16;
    cb->bSize = 16;
    cb->wPieces = malloc(sizeof(Piece*) * cb->wSize);
    cb->bPieces = malloc(sizeof(Piece*) * cb->bSize);

    __createDefaultWhitePieces(cb->wPieces);
    __createDefaultBlackPieces(cb->bPieces);

    __populateChess(cb);

    printf("Chess successfully created\n");

    return cb;
}

void __freeChessPieces(Piece** pieces, int size)
{
    for (int i = 0; i < size; i++)
    {
        // First free position which is malloc
        free(pieces[i]->pos);
        free(pieces[i]);
    }
    free(pieces);
}

void cleanChess(ChessBoard* cb)
{
    // First we should free all the pieces
    __freeChessPieces(cb->wPieces, cb->wSize);
    __freeChessPieces(cb->bPieces, cb->bSize);

    // Now free chess
    free(cb);
}
