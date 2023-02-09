#include "Game.h"
#include "Engine.h"
#include "Move.h"
#include "Snapshot.h"
#include <memory>
#include <thread>
#include "GameControler.h"
#include <chrono>

void Game::run()
{
    
 
    Engine E1{ position, !color,this->level };

    std::shared_ptr<Snapshot> Prev(position->make_snapshot());
    std::shared_ptr<Snapshot> Prev2 = Prev;
    std::string task;
    while ( position->is_exist_legal_move())
    {
        task = this->input->pop();
        if ( not task.empty())
        {
            if (task[0] =='1')
            {
                Prev->restore();
                Prev2 = Prev;

            }
            else if (task[0] == '2')
                return;
            else if( position->color() == this->color)
            {
                
                position->make_legal_move(task);
            }
               
        }
        else if (position->color() != this->color)
        {
            
            E1.alfabeta();
            output->push(position->last_move());
            Prev = Prev2;
            Prev2 = std::shared_ptr<Snapshot> (position->make_snapshot());
            
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::duration<float>{0.30});
            std::this_thread::yield();
        }
    }
    output->push("2");
}

Game::Game(bool color, int level, MyQueue& input, MyQueue& output,  Position &position)
{
    this->level = level;
    this->color = color;
    this->input = &input;
    this->output = &output;
    this->position = &(position);
}

Game::~Game()
{
 
    position = nullptr;
    this->input = nullptr;
    this->output = nullptr;
}

