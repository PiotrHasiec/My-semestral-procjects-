#pragma once
const float pieces_value[6]{ 1,3,3.1,5,14,20 };
const float positional_value[6][8][8]{
    {
    {0,  0,  0,  0,  0,  0,  0,  0},
    {50, 50, 50, 50, 50, 50, 50, 50},
    {10, 10, 20, 30, 30, 20, 10, 10},
    { 5,  5, 10, 25, 25, 10,  5,  5},
    {1,  1,  1, 20, 20,  1,  1,  1},
    {5, -5,-10,  1,  1,-10, -5,  5 },
    {5, 10, 10,-20,-20, 10, 10,  5},
    {0,  0,  0,  0,  0,  0,  0,  0}},

    {
    {-50,-40,-30,-30,-30,-30,-40,-50},
    {-40,-20,  0,  0,  0,  0,-20,-40},
    {-30,  1, 10, 15, 15, 10,  1,-30},
    {-30,  5, 15, 20, 20, 15,  5,-30},
    {-30,  1, 15, 20, 20, 15,  1,-30},
    {-30,  5, 10, 15, 15, 10,  5,-30 },
    {-40,-20,  1,  5,  5,  1,-20,-40},
    {-50,-40,-30,-30,-30,-30,-40,-50}},

    {
    {-20,-10,-10,-10,-10,-10,-10,-20},
    {-10,  1,  1,  1,  1,  1,  1,-10},
    {-10,  1,  5, 10, 10,  5,  1,-10 },
    {-10,  5,  5, 10, 10,  5,  5,-10},
    {-10,  0, 10, 10, 10, 10,  0,-10},
    {-10, 10, 10, 10, 10, 10, 10,-10},
    {-10,  5,  1,  1,  1,  1,  5,-10},
    {-20,-10,-10,-10,-10,-10,-10,-20}},

    {
    {1,  1,  1,  1,  1,  1,  1,  1},
    {5, 10, 10, 10, 10, 10, 10,  5},
    {-5,  1,  1,  1,  1,  1,  1, -5 },
    {-5,  1,  1,  1,  1,  1,  1, -5},
    {-5,  1,  1,  1,  1,  1,  1, -5},
    {-5,  1,  1,  1,  1,  1,  1, -5},
    {-5,  1,  1,  1,  1,  1,  1, -5},
    {1,  1,  1,  5,  5,  1,  1,  1}},

    {
    {-20,-10,-10, -5, -5,-10,-10,-20},
    {-10,  1,  1,  1,  1,  1,  1,-10},
    {-10,  1,  5,  5,  5,  5,  1,-10 },
    {-5,  1,  5,  5,  5,  5,  1, -5},
    { 1,  1,  5,  5,  5,  5,  1, -5},
    {-10,  5,  5,  5,  5,  5,  1,-10},
    {-10,  1,  5,  1,  1,  1,  1,-10},
    {-20,-10,-10, -5, -5,-10,-10,-20}},

    {
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30 },
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-20,-30,-30,-40,-40,-30,-30,-20},
    {-10,-20,-20,-20,-20,-20,-20,-10},
    {20, 20,  1,  1,  1,  1, 20, 20},
    { 20, 30, 10,  1,  1, 10, 30, 20}},

};