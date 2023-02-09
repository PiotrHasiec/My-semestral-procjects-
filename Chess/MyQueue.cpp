#include "MyQueue.h"

void MyQueue::push(std::string task)
{
    std::lock_guard<std::mutex> lock(mtx_task);
    tasks.push(task);
}

std::string MyQueue::pop()
{
    std::lock_guard<std::mutex> lock(mtx_task);
    std::string task;
    if (not tasks.empty())
    {
        task = tasks.front();
        tasks.pop();
    }
    else
    {
        task = std::string();
    }
    

    return task;
}




