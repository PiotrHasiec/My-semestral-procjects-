#include "Engine.h"
#include <cmath>
#include <set>
#include "node.h"
#include "Move.h"
#include <limits>

Engine::Engine(Position* p, bool color, int depth)
{
	pozycja = p; this->color = color; this->depth = depth;
	additional_depth = 0;
	Position to_compute_max_leavs;
	Node root{ (*pozycja),1 };

	root.alfabeta(depth, depth, -FLT_MAX, FLT_MAX, color);
	std::cout<< root.getleafs();
	maxleafcount = lastleafs = root.getleafs();
}

int Engine::make_move()
{
	std::set<Move> moves;
 for(int i = 0; i<8; i++)
	 for (int j = 0; j < 8; j++)
	 {
		 if ((*pozycja).p_color(i,j) == this->color and (*pozycja)[i][j] != 0)
		 {
			 auto tmp = pozycja->legalmove(i, j);
			 moves.insert(tmp.begin(),tmp.end());
			 
		 }
	 }
 if (moves.begin() != moves.end())
 {
	 Move move = *moves.begin();
	 this->pozycja->make_legal_move(move.tonot(!this->color));
	 return 0;
 }
 else
	 return 1;

}
int Engine::make_move_2()
{
	
	Node root{ *pozycja,this->color };
	root.add_childs();
	
	if ( color)
	{
		if (root.max().last_move() != "0000")
		{
			this->pozycja->make_legal_move(root.max().last_move());
			std::cout << (*pozycja).evaluation() << std::endl;
			
			return 0;
		}
	}
	else
	{
		if (root.min().last_move() != "0000")
		{
			this->pozycja->make_legal_move(root.min().last_move());
			std::cout << (*pozycja).evaluation() << std::endl;
			
			return 0;
		}
	}

	return 1;

}

int Engine::make_move_3()
{
	
	int addition_depth = Position{}.gamephase() / (*pozycja).gamephase();

	Node root{ *pozycja,this->color };
	root.build_tree(depth+1 + addition_depth, color);
	this->pozycja->make_move(root.maxmin().last_move());
	
	return 0;
}



int Engine::alfabeta()
{
	float k = std::pow(this->lastleafs, 1.0 / (depth + additional_depth));
	int tmp_additional_depth  = std::log((this->maxleafcount)) / std::log(k) - depth;
	//std::cout << tmp_additional_depth << " " << additional_depth << std::endl;
	additional_depth = std::min(tmp_additional_depth, additional_depth + 2);
	//std::cout << additional_depth << " "<< this->lastleafs <<std::endl;
	
	Node root{ *pozycja,this->color };
	try {
		root.alfabeta(depth ,depth , -FLT_MAX, FLT_MAX, color);
		lastleafs = root.getleafs();
		 
		std::cout << lastleafs << "\n";
		root.build_tree(depth, color);
		std::cout << root.getleafs() << "\n";
	}
	catch (std::exception& e)
	{
		this->depth -= 1;
		return 1;
	}
	
	this->pozycja->make_move(root.maxmin().last_move());
	return 0;
}
