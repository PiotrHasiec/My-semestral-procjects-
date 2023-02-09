#pragma once
#include <mutex>
#include <queue>
class MyQueue
{

	std::queue <std::string> tasks;
    mutable std::mutex mtx_task;
public:
	void push(std::string task);
	std::string pop();
	
};

