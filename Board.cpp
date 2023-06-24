#include "board.h"

const int BOARD_SIZE = 8;
Piece board[BOARD_SIZE][BOARD_SIZE];

void initializeBoard() {
    //Figuren auf Startpositionen Setzen
    //Weiﬂe Figuren
    board[0][0] = { ROOK, WHITE };
    board[0][1] = { KNIGHT, WHITE };
    board[0][2] = { BISHOP, WHITE };
    board[0][3] = { QUEEN, WHITE };
    board[0][4] = { KING, WHITE };
    board[0][5] = { BISHOP, WHITE };
    board[0][6] = { KNIGHT, WHITE };
    board[0][7] = { ROOK, WHITE };
    for (int i = 0; i < BOARD_SIZE; ++i) 
        board[1][i] = { PAWN, WHITE };

    //Schwarze Figuren
    board[7][0] = { ROOK, BLACK };
    board[7][1] = { KNIGHT, BLACK };
    board[7][2] = { BISHOP, BLACK };
    board[7][3] = { QUEEN, BLACK };
    board[7][4] = { KING, BLACK };
    board[7][5] = { BISHOP, BLACK };
    board[7][6] = { KNIGHT, BLACK };
    board[7][7] = { ROOK, BLACK };
    for (int i = 0; i < BOARD_SIZE; ++i) 
        board[6][i] = { PAWN, BLACK };
    
    //Restliche Felder Leer Setzen
    for (int i = 2; i < 6; ++i) 
        for (int j = 0; j < BOARD_SIZE; ++j) 
            board[i][j] = { EMPTY, WHITE };
 
}
