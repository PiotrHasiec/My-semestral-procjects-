#pragma once
#include "Position.h"
#include <string>
enum type { beats, Enpasse, Castling_oo, Castling_ooo,by2, Normal,  no_type};
class Move
{
	friend class Position;
	char xstart;
	char ystart;
	char xend;
	char yend;
	type move_type;
public:
	Move(char, char, char, char, type);
	Move(int, int, int, int);
	bool operator <(Move);
	friend bool operator < (Move, Move);
	bool operator >(Move);
	bool operator == (Move);
	std::string tonot(bool color);
};

