#ifndef CONSTANTS_h
#define CONSTANTS_h

enum piece_type
{
    PAWN = 1, KNIGHT, BISHOP, ROOK, QUEEN, KING
};
enum piece
{
    W_PAWN = PAWN, W_KNIGHT, W_BISHOP, W_ROOK, W_QUEEN, W_KING,
    B_PAWN = PAWN + 8, B_KNIGHT, B_BISHOP, B_ROOK, B_QUEEN, B_KING
};
const int start_poss[8][8]{ {B_ROOK,B_KNIGHT,B_BISHOP,B_QUEEN,B_KING,B_BISHOP,B_KNIGHT,B_ROOK},
                                         {B_PAWN,B_PAWN,B_PAWN,B_PAWN,B_PAWN,B_PAWN,B_PAWN,B_PAWN,},
                                         {0,0,0,0,0,0,0,0},
                                         {0,0,0,0,0,0,0,0},
                                         {0,0,0,0,0,0,0,0},
                                         {0,0,0,0,0,0,0,0},
                                         {W_PAWN,W_PAWN,W_PAWN,W_PAWN,W_PAWN,W_PAWN,W_PAWN,W_PAWN,},
                                         {W_ROOK,W_KNIGHT,W_BISHOP,W_QUEEN,W_KING,W_BISHOP,W_KNIGHT,W_ROOK} };




#endif