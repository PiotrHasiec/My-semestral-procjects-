#pragma once
#include <iostream>
#include <vector>
#include <set>
#include "Game.h"
#include "node.h"
#include "Move.h"
#include <mutex>

class Snapshot;
class Move;
class Position_hash;
class Node;
class Move;
class Position
{
	
	//std::recursive_mutex mtx_all;
	friend class Position_hash;
	
protected:
	
	bool move = 1;
	bool OO = 1;
	bool OOO = 1;
	bool oo = 1;
	bool ooo = 1;
	int enpasse = -1;
	std::vector<std::vector <int>> pos;
	std::string LastMove="0000";
	std::set<Move> pawn_move_normal(int, int);
	std::set<Move> pawn_move_2(int, int);
	std::set<Move> pawn_move_enpasse(int, int);
	std::set<Move> knight_move(int, int);
	std::set<Move> bishop_move(int, int);
	std::set<Move> rook_move(int, int);
	std::set<Move> queen_move(int, int);
	std::set<Move> king_move_normal(int, int);
	std::set<Move> king_catling(int, int);
public:
	bool color() { return this->move; };
	Position();
	Position(Position&);
	Position* make_move(std::string);
	Position* make_legal_move(std::string);
	Snapshot* make_snapshot();
	void set_state(bool move, bool OO, bool OOO, bool oo, bool ooo, int enpasse, std::vector<std::vector <int>> pos, std:: string LastMove);
	void print();
	std::set<Move> pseudolegalmove(int , int);
	std::set<Move> legalmove(int x, int y);
	bool p_color(int, int);
	bool in(int, int);
	float evaluation();
	float gamephase();
	std::vector <int> operator[](int x);
	Position& operator=(const Position&);
	std::string last_move();
	bool is_exist_legal_move();
};


class Position_hash
{
	std::size_t operator()(const Position& f) const
	{
		int h = 0;
		std::hash<int> r;
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
			{
				if (f.pos[i][j])
				{
					h = h ^ f.pos[i][j];
				}
			}
		return r(h);

	}
};




