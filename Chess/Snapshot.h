#pragma once
#include "Position.h"
class Snapshot : protected Position
{

	Position* position;

public:
	Snapshot(Position*, bool move, bool OO, bool OOO, bool oo, bool ooo, int enpasse, std::vector<std::vector <int>> pos, std:: string LastMove);
	void restore();
	
};

