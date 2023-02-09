#include "node.h"
#include <set>
#include <unordered_set>
#include "Move.h"
#include <thread>
#include <limits>
void Node::add_childs()
{
	
	std::set<Move> possible_moves;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (Pos->p_color(i, j) == this->color and (*Pos)[i][j] != 0)
			{
				auto tmp = Pos->pseudolegalmove(i, j);
				possible_moves.insert(tmp.begin(), tmp.end());

			}
		}
	
		this->NextNodes = std::shared_ptr<Node[]>(new Node[possible_moves.size()]);
	
	size = possible_moves.size();
	int j = 0;
	Move tmp{ 0,0,0,0 };
	for (auto i = possible_moves.begin(); i != possible_moves.end(); i++)
	{
		tmp = *i;
		Position tmp2 = *(this->Pos);
		this->NextNodes[j].set_position( tmp2.make_move( tmp.tonot(0)), !this->color );
		if(this)
			this->NextNodes[j].set_state(this);
			j++;
	}
}

void Node::add_legal_childs()
{

	std::set<Move> possible_moves;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (Pos->p_color(i, j) == this->color and (*Pos)[i][j] != 0)
			{
				auto tmp = Pos->legalmove(i, j);
				possible_moves.insert(tmp.begin(), tmp.end());

			}
		}

	this->NextNodes = std::shared_ptr<Node[]>(new Node[possible_moves.size()]);
	size = possible_moves.size();
	int j = 0;
	Move tmp{ 0,0,0,0 };
	for (auto i = possible_moves.begin(); i != possible_moves.end(); i++)
	{
		tmp = *i;
		Position tmp2 = *(this->Pos);
		this->NextNodes[j].set_position(tmp2.make_move(tmp.tonot(0)), !this->color);
		if (this)
			this->NextNodes[j].set_state(this);
		j++;
	}
}

void Node::set_position(Position* pos,bool color)
{
	if (this->Pos)
		delete Pos;
	Pos = new Position(*pos);
	this->color = color;
	this->size = 0;
	evaluation = Pos->evaluation();
}

Node::Node()
{
	//this->parent = parent;
	
	this->Pos = new Position;
	this->color = 0;
	this->size = 0;
}
void Node::set_state(Node* parent)
{
	this->parent = parent;
	this->color = !parent->color;
	
}
Node::Node(Position pos,bool color)
{
	
	this->Pos = new Position{ pos };
	this->color = color;
	this->size = 0;
}
Node::~Node()
{
	if (this) {
		if (this->Pos)
		{
			delete Pos;
			Pos = nullptr;
		}
		if (this->NextNodes)
		{
			
			NextNodes = nullptr;
		}
	}
}


Position Node::max()
{
	Position returnn;
	if (this->size == 0) return returnn ;
	int max = 0;
	for (int i = 1; i < size; i++)
		if (NextNodes[i].Pos->evaluation() > NextNodes[max].Pos->evaluation())
			max = i;
	return *(NextNodes[max].Pos);
}

Position Node::min()
{
	Position returnn;
	if (this->size == 0) return returnn;
	int min = 0;
	for (int i = 1; i < size; i++)
		if (NextNodes[i].Pos->evaluation() < NextNodes[min].Pos->evaluation())
			min = i;
	return *(NextNodes[min].Pos);
}

float Node::max_n()
{
	if (this->size == 0) return 0;
	int max = 0;
	for (int i = 1; i < size; i++)
		if (NextNodes[i].evaluation > NextNodes[max].evaluation)
			max = i;
	return NextNodes[max].evaluation;
}

float  Node::min_n()
{
	if (this->size == 0)  return 0;
	int min = 0;
	for (int i = 1; i < size; i++)
		if (NextNodes[i].evaluation < NextNodes[min].evaluation)
			min = i;
	return NextNodes[min].evaluation;
	
}

void Node::thread_build(int hight, int start, int end, bool p_color)
{
	for (int i = start; i < end; i++)
	{
		this->NextNodes[i].build_tree(hight - 1, p_color);
	}
}

Position Node::maxmin()
{
	Position v_return;
	for (int i = 0; i < size; i++)
		if (NextNodes[i].evaluation == evaluation)
		{
			//auto tmp = std::move(NextNodes[i]);
			v_return = *(NextNodes[i].Pos);
			break;
		}
	return v_return;
}

void Node::build_tree(int hight, bool p_color)
{
	
	
	if (hight)
	{
		this->add_legal_childs();
		/*if (hight == 4) {
			std::thread t1(&Node::thread_build, this, hight,0, size/4, p_color);
			std::thread t2(&Node::thread_build, this, hight, size / 4 + 1, size/2, p_color);
			std::thread t3(&Node::thread_build, this, hight,size/2+1, 3*size/4, p_color);
			std::thread t4(&Node::thread_build, this, hight, 3 * size / 4 + 1, size, p_color);
			
			
			t1.join();
			t2.join();
			t3.join();
			t4.join();


			for (int i = 0; i < size; i++)
			{this->NextNodes[i].build_tree(hight - 1, p_color);
			if (color)
			{
				this->evaluation = this->max_n();
			}
			else
			{
				this->evaluation = this->min_n();
			}
		}
		else
			*/
		{
			if (color == p_color )
			{

				for (int i = 0; i < size; i++)
				{
					this->NextNodes[i].build_tree(hight - 1, p_color);
					this->leafs += NextNodes[i].leafs;
				}
			}
			else
			{
				for (int i = 0; i < size; i++)
				{
					this->NextNodes[i].build_tree(hight - 1, p_color);
					this->leafs += NextNodes[i].leafs;
				}
			}
			if (color)
			{
				this->evaluation = this->max_n();
			}
			else
			{
				this->evaluation = this->min_n();
			}
			
		}
		
	
	}
	else
	{
		this->evaluation = this->Pos->evaluation();
		this->leafs = 1;
	}
	
}






float Node::alfabeta(int depth, int hight, float alfa, float beta, bool color)
{
	if (hight == 0)
	{
		leafs = 1;
		return this->Pos->evaluation();
	}
	try {
		//if (hight >= depth - 1)
			this->add_legal_childs();
		//else
			//this->add_childs();
	}
	catch (std::exception& e)
	{
		return this->Pos->evaluation();
		throw;
	}

	if (this->color)
	{
		float tmp_alfa = alfa;
		int i = 0;
		for (i = 0; i < size; i++)
		{
			tmp_alfa = NextNodes[i].alfabeta(depth, hight - 1, alfa, beta, color);
			this->leafs += NextNodes[i].leafs;
			if (tmp_alfa > alfa)
				alfa = tmp_alfa;
			if (alfa >= beta)
				break;
		}

		
		this->evaluation = alfa;
		
		return alfa;

	}
	else
	{



		float tmp_beta = beta;
		int i = 0;

		for (i = 0; i < size; i++)
		{
			tmp_beta = NextNodes[i].alfabeta(depth, hight - 1, alfa, beta, color);
			this->leafs += NextNodes[i].leafs;
			if (tmp_beta < beta)
				beta = tmp_beta;
			if (alfa >= beta)
				break;
		}
		

		this->evaluation = beta;
		return beta;
	}
	
}
bool Node::is_legal()
{
	
		this->add_childs();
		for (int i = 0; i < size; i++)
		{
			float evaluation = NextNodes[i].Pos->evaluation();
			if (evaluation == FLT_MAX or evaluation == -FLT_MAX)
				return false;
		}
		return true;
		
}

float Node::evaluation_v()
{
	return this->evaluation;
}
