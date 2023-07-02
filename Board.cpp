#include "board.h"

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
        } else if (rowOffset == 2 * forwardDirection && srcRow == (piece.color == WHITE ? 6 : 1)) {
            if (board[destRow][destCol].type == EMPTY && board[srcRow + forwardDirection][srcCol].type == EMPTY) {
                    return true;
                }
            }

    }
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

void makeMove(const Move& move) {
    //Ausgangs und Ziel Felder abrufen der Bewegung

    int srcRow = move.source.row;
    int srcCol = move.source.column;
    int destRow = move.destination.column;
    int destCol = move.destination.column;

    Piece piece = board[srcRow][srcCol];
    board[srcRow][srcCol] = {EMPTY, EMPTY};
    
    Piece capturedPiece = board[destRow][destCol];
    if(capturedPiece.type != EMPTY) {
        if (capturedPiece.color == WHITE) {
            whiteCapturedCount += getPieceValue(capturedPiece.type);
        } else {
                blackCapturedCount += getPieceValue(capturedPiece.type);
        }
        
        removePiece(destRow, destCol);   
    }      
    
    if (piece.type == PAWN) {
        // Check for en passant
        if (/* Condition to check en passant */) {
            // Handle en passant
            // Remove the captured pawn from the board
            int captureRow = /* Calculate the row of the captured pawn */;
            int captureCol = destCol; // The captured pawn is on the same column as the destination square
            removePiece(captureRow, captureCol);
        }
    } else if (piece.type == KING) {
        // Check for castling
        if (/* Condition to check castling */) {
            // Handle castling
            if (destCol > srcCol) {
                // Perform kingside castling
                int rookSrcCol = BOARD_SIZE - 1; // Column of the rook on the kingside
                int rookDestCol = destCol - 1; // Column of the rook's destination square
                Piece rook = board[destRow][rookSrcCol];
                // Update the source square of the rook to be empty
                board[destRow][rookSrcCol] = {EMPTY, EMPTY};
                // Update the destination square of the rook with the rook piece
                board[destRow][rookDestCol] = rook;
            } else {
                // Perform queenside castling
                int rookSrcCol = 0; // Column of the rook on the queenside
                int rookDestCol = destCol + 1; // Column of the rook's destination square
                Piece rook = board[destRow][rookSrcCol];
                // Update the source square of the rook to be empty
                board[destRow][rookSrcCol] = {EMPTY, EMPTY};
                // Update the destination square of the rook with the rook piece
                board[destRow][rookDestCol] = rook;
            }
        }
    
        board[destRow][destCol] = piece;
    }
}