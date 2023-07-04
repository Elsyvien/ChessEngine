#ifndef BOARD_H
#define BOARD_H

enum PieceType { EMPTY, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING };
enum PieceColor { WHITE, BLACK };

struct Piece {
    PieceType type;
    PieceColor color;
};

struct Position {
    int row;
    int column;
};

struct Move {
    Position source;
    Position destination;
};

extern const int BOARD_SIZE;
extern Piece board[BOARD_SIZE][BOARD_SIZE];

extern int whiteCapturedCount;
extern int blackCapturedCount;
extern bool BRook1Moved, BRook2Moved, WRook1Moved, WRook2Moved;

extern const int PAWN_VALUE, ROOK_VALUE, KNIGHT_VALUE, BISHOP_VALUE, QUEEN_VALUE, KING_VALUE;

void initializeBoard();
void printBoard();
bool isValidMove(const Move& move);
void makeMove(const Move& move);
void movePiece(int srcRow, int srcCol, int destRow, int destCol);
void capturePiece(int row, int col);
bool isCastleMove(const Move& move);
void moveRookForCastle(const Move& move);
bool isEnPassantCapture(const Move& move);
void performEnPassantCapture(const Move& move);

#endif 