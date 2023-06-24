#ifndef BOARD_H
#define BOARD_H

enum PieceType { EMPTY, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING };
enum PieceColor { WHITE, BLACK };

struct Piece {
    PieceType type;
    PieceColor color;
};

extern const int BOARD_SIZE;
extern Piece board[BOARD_SIZE][BOARD_SIZE];

void initializeBoard();


#endif 