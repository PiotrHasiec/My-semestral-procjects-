#pragma once
#include "MyQueue.h"
#include "Position.h"
class Position;
class MyQueue;
class Game
{
	bool color;
	int level;
	MyQueue* input;
	MyQueue* output;
	Position* position;
public:
	void run();
	Game(bool color, int level, MyQueue& input, MyQueue& output,  Position &position);
	~Game();
};

