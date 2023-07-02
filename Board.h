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

extern int whiteCapturedCount;
extern int blackCapturedCount;

extern const int PAWN_VALUE, ROOK_VALUE, KNIGHT_VALUE, BISHOP_VALUE, QUEEN_VALUE, KING_VALUE;

void initializeBoard();
bool isValidMove(const Move& move);
void makeMove(const Move& move);
void removePiece(int row, int col);
int getPieceValue(PieceType type);

#endif 