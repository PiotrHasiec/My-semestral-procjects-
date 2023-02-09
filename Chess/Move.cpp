#include "Move.h"

Move::Move(char xstart, char ystart, char xend, char yend, type move_type = type::Normal)
{

	this->xstart = xstart;
	this->ystart = ystart;
	this->xend = xend;
	this->yend = yend;
	this->move_type = move_type;
}


Move::Move(int xstart, int ystart, int xend, int yend)
{
	this->xstart = xstart;
	this->ystart = ystart;
	this->xend = xend;
	this->yend = yend;
	this->move_type = type::no_type;
}

bool Move::operator<(Move m)
{
	if (this->xstart < m.xstart and this->ystart < m.ystart)
		return true;
	else
		return false;
}

bool Move::operator>(Move m)
{
	return !this->operator<(m);
}

bool Move::operator==(Move m)
{
	if(this->xstart == m.xstart and this->ystart == m.ystart and this->xend==m.xend and this->yend == m.xend)
		return true;
	return false;
}

bool operator<(Move m1, Move m)
{

	bool r;
	int t1 = (m1.xstart + 8 * m1.xend + 64 * m1.ystart + 512 * m1.yend + 3584* m1.move_type);
	int t2 = (m.xstart + 8 * m.xend + 64 * m.ystart + 512 * m.yend + 3584 * m1.move_type);
	r = t1 < t2;

		return r;
	
}

std::string Move::tonot(bool color)
{
	char r[5]{};
	
	
		r[0] = 'a' + static_cast<char> (ystart);
		r[1] = '8' - static_cast<char> (xstart);
		r[2] = 'a' + static_cast<char> (yend);
		r[3] = '8' - static_cast<char> (xend );

	
	r[4] = 0;


	return std::string(r);
}