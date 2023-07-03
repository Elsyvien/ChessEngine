#include <iostream>
#include "Board.h"

using namespace std;

const int BOARD_SIZE = 8;
Piece board[BOARD_SIZE][BOARD_SIZE];

int whiteCapturedCount = 0;
int blackCapturedCount = 0;

const int PAWN_VALUE = 1;
const int ROOK_VALUE = 5;
const int KNIGHT_VALUE = 3;
const int BISHOP_VALUE = 3;
const int QUEEN_VALUE = 9;
const int KING_VALUE = 0;



void initializeBoard() {
    //Figuren auf Startpositionen Setzen
    //Weiße Figuren
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
            board[i][j] = { EMPTY, EMPTY };

}

bool isValidMove(const Move& move) {
    int srcRow = move.source.row;
    int srcCol = move.source.column;
    int destRow = move.destination.column;
    int destCol = move.destination.column;

    Piece piece = board[srcRow][srcCol];

    if (destRow < 0 || destRow >= BOARD_SIZE || destCol < 0 || destCol >= BOARD_SIZE)
        return false;

    if (board[destRow][destCol].color == piece.color)
        return false;

    int rowOffset = destRow - srcRow;
    int colOffset = destCol - srcCol;

    switch (piece.type) {
    case PAWN: {
        int forwardDirection = (piece.color == WHITE) ? -1 : 1;
        if (colOffset == 0) {
            if (board[destRow][destCol].type == EMPTY)
                return true;
        }
        else if (rowOffset == 2 * forwardDirection && srcRow == (piece.color == WHITE ? 6 : 1)) {
            if (board[destRow][destCol].type == EMPTY && board[srcRow + forwardDirection][srcCol].type == EMPTY)
                return true;
        }
        else if (std::abs(colOffset) == 1 && rowOffset == forwardDirection) {
            if (board[destRow][destCol].type != EMPTY)
                return true;
        }
        break;
    }
    case ROOK: {
        if (rowOffset != 0 && colOffset != 0)
            return false;

        int rowStep = (rowOffset != 0) ? rowOffset / std::abs(rowOffset) : 0;
        int colStep = (colOffset != 0) ? colOffset / std::abs(colOffset) : 0;
        int row = srcRow + rowStep;
        int col = srcCol + colStep;
        while (row != destRow || col != destCol) {
            if (board[row][col].type != EMPTY)
                return false;

            row += rowStep;
            col += colStep;
        }
        return true;
    }
    case KNIGHT: {
        if ((std::abs(rowOffset)) == 2 && std::abs(colOffset) == 1 || (std::abs(rowOffset) == 1 && std::abs(colOffset) == 2))
            return true;
    }
    case BISHOP: {
        if (std::abs(rowOffset) != std::abs(colOffset)) {
            return false;
        }
        int rowStep = (rowOffset > 0) ? 1 : -1;
        int colStep = (colOffset > 0) ? 1 : -1;
        int row = srcRow + rowStep;
        int col = srcCol + colStep;
        while (row != destRow && col != destCol) {
            if (board[row][col].type != EMPTY)
                return false;
        row += rowStep;
        col += colStep;
        }
        return true;
    }
    case QUEEN: {
        if (rowOffset == 0 || colOffset == 0 || std::abs(rowOffset) == std::abs(colOffset)) {
            int rowStep = (rowOffset != 0) ? rowOffset / std::abs(rowOffset) : 0;
            int colStep = (colOffset != 0) ? colOffset / std::abs(colOffset) : 0;
            int row = srcRow + rowStep;
            int col = srcRow + rowStep;
            while (row != destRow || col != destCol) {
                if (board[row][col].type != EMPTY) 
                    return false;
            row += rowStep;
            col += colStep;
            }
            return true;
        } 
        break;
    }
    case KING: {
        if (std::abs(rowOffset) <= 1 && std::abs(colOffset) <= 1) 
            return true; 
        
        break;
    }
    default:
        return false;
    }
    return false;
}

void removePiece(int row, int col) {
    board[row][col] = {EMPTY, EMPTY};
}

int getPieceValue(PieceType type) {
    switch (type) {
        case PAWN:
            return PAWN_VALUE;
        case ROOK:
            return ROOK_VALUE;
        case KNIGHT:
            return KNIGHT_VALUE;
        case BISHOP:
            return BISHOP_VALUE;
        case QUEEN:
            return QUEEN_VALUE;
        default:
            return KING_VALUE;
    }
}

void movePiece(int srcRow, int srcCol, int destRow, int destColumn) {
    Move move;
    move.source.row = srcRow;
    move.source.column = srcCol;
    move.destination.row = destRow;
    move.destination.column = destColumn;

    if(isValidMove(move)) {
        board[destRow][destColumn] = board[srcRow][srcCol];
        board[destRow][destColumn] = board[srcRow][srcCol];
    }
}

void makeMove(const Move& move) {
    int srcRow = move.source.row;
    int srcCol = move.source.column;
    int destRow = move.destination.row;
    int destCol = move.destination.column;

    movePiece(srcRow, srcCol, destRow, destCol);

    if (board[destRow][destCol].type != EMPTY) {
        capturePiece(destRow, destCol);
    }

    if (isCastleMove(move)) {
        moveRookForCastle(move);
    }

    if (isEnPassantCapture(move)) {
        performEnPassantCapture(move);
    }
}