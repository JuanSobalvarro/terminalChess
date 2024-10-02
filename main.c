/*
 * Compile: gcc -o chess main.c chess.c terminalcolors.c
*/
#include "chess.h"

int main()
{
    RGB whitefg = {255, 255, 255};
    RGB blackfg = {255, 69, 0};
    RGB whitebg = {200, 200, 200};
    RGB blackbg = {80, 80, 80};
    ChessBoard* cb = createChess(whitefg, blackfg, whitebg, blackbg);
    printChess(cb);

    cleanChess(cb);
    return 0;
}