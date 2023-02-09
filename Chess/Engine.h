#pragma once
#include "Position.h"
#include<SFML/Window.hpp>



class Engine 	
{
	int depth = 3;
	int maxleafcount;
	int lastleafs;
	int additional_depth;
	Position* pozycja;
	bool color = 1;
public:
	Engine(Position* p, bool color, int depth);
	int make_move();
	int make_move_2();
	int make_move_3();

	int alfabeta();
};