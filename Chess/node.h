#pragma once
#include "Position.h"
#include <memory>
class Position;
class Node
{
	std::shared_ptr<Node[]> NextNodes;
	Position* Pos;
	float evaluation = 0;
	Node* parent = nullptr;
	bool color;
	bool set = 0;
	int size;
	int leafs = 0;
	void set_position(Position* pos, bool color);
public:
	void add_childs();
	void add_legal_childs();
	//node();
	Node();
	void set_state(Node* parent);
	Node(Position pos, bool color);
	~Node();
	
	Position  max();
	Position  min();
	float  max_n();
	float  min_n();
	void thread_build(int hight, int start, int end, bool p_color);
	Position maxmin();
	void  build_tree(int hight, bool p_color);
	
	float alfabeta(int depth, int hight, float alfa, float beta, bool color);
	bool is_legal();
	int getleafs() { return leafs; }
	float evaluation_v();
};

