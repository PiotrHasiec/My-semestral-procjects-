#pragma once
#include "Field.h"
#include "SFML/Graphics.hpp"
#include "Position.h"
#include "MyQueue.h"
#include <memory>
#include <queue>
class Position;
class GameControler
{
    float size;
    bool color;
    sf::RenderWindow window;
    std::unique_ptr<Gameboard> b1;
    std::vector<sf::Sprite> pieces_s;
    std::vector<sf::Texture> pieces;
    sf::View view;
    Position position;
    void draw_from_position(Position);
    void resize();
    void draw(int &n);
    MyQueue input;
    MyQueue  output;
public:
    GameControler(bool color, float size);
    ~GameControler();
    void Run();
    std::string tonot(float,float,float,float);
};


