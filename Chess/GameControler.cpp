#include "GameControler.h"
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include <vector>
#include "Gameboard.h"

#include <stdexcept>
#include <chrono>
#include "Button.h"
#include "Menu.h"
#include "Constants.h"




void GameControler::draw_from_position(Position p)
{
    window.clear(sf::Color(46, 46, 46, 255));
    window.draw(*b1);

    int piece = 0;
    int n = 0;
    this->pieces_s.clear();
    if (color)
        for (int i = 0; i < 8; i++)
        {


            for (int j = 0; j < 8; j++) {
                if (p[i][j])
                {

                    pieces_s.push_back(sf::Sprite{});
                    pieces_s[n].setTexture(pieces[p[i][j]]);
                    pieces_s[n].setScale(4 * size / 5 / pieces[p[i][j]].getSize().y, 4 * size / 5 / pieces[p[i][j]].getSize().y);
                    pieces_s[n].setOrigin(pieces[p[i][j]].getSize().x / 2, pieces[p[i][j]].getSize().y / 2);
                    pieces_s[n].setPosition(size * (j + 1) + size / 2, size * (i + 1) + size / 2);
                    if (n == 32) break;
                    n++;
                }
                if (n == 32) break;
            }

        }
    else
        for (int i = 0; i < 8; i++)
        {


            for (int j = 0; j < 8; j++) {
                if (p[i][j])
                {

                    pieces_s.push_back(sf::Sprite{});
                    pieces_s[n].setTexture(pieces[p[i][j]]);
                    pieces_s[n].setScale(4 * size / 5 / pieces[p[i][j]].getSize().y, 4 * size / 5 / pieces[p[i][j]].getSize().y);
                    pieces_s[n].setOrigin(pieces[p[i][j]].getSize().x / 2, pieces[p[i][j]].getSize().y / 2);
                    pieces_s[n].setPosition(size * (8 - j) + size / 2, size * (8 - i) + size / 2);
                    if (n == 32) break;
                    n++;
                }
                if (n == 32) break;
            }

        }
    for (int i = 0; i < pieces_s.size(); i++)
    {

        window.draw(pieces_s[i]);
    }
    window.display();
}

void GameControler::resize()
{
    size = window.getSize().y / 10;
    window.setSize(sf::Vector2u(10 * size, 10 * size));
    view.setSize(10 * size, 10 * size);
    view.setCenter(5 * size, 5 * size);
    window.setView(view);
    b1->resize(size);
    
}

void GameControler::draw(int &n)
{
    
    window.clear(sf::Color(46, 46, 46, 255));
    window.draw(*b1);
    for (int i = 0; i < pieces_s.size(); i++)
    {

        window.draw(pieces_s[i]);
    }
    if(n < pieces_s.size())
        window.draw(pieces_s[n]);
    window.display();
}
GameControler::GameControler(bool color, float size)
{
    this->size = size;
    this->color = color;
    window.setSize(sf::Vector2u{ (unsigned int)size,(unsigned int)size });
    window.create(sf::VideoMode(10 * size, 10 * size), "");
    window.setFramerateLimit(60);
    sf::View view = window.getView();
   
   
    b1 = std::move(std::unique_ptr<Gameboard> {new Gameboard{ size, size, color, size } });
    
    for (int i = 0; i < 15; i++)
    {
        pieces.push_back(sf::Texture{});
    }
    pieces[W_KING].loadFromFile("chess/K_W.png");
    pieces[B_KING].loadFromFile("chess/K_B.png");
    pieces[W_QUEEN].loadFromFile("chess/Q_W.png");
    pieces[B_QUEEN].loadFromFile("chess/Q_B.png");
    pieces[W_ROOK].loadFromFile("chess/R_W.png");
    pieces[B_ROOK].loadFromFile("chess/R_B.png");
    pieces[W_BISHOP].loadFromFile("chess/B_W.png");
    pieces[B_BISHOP].loadFromFile("chess/B_B.png");
    pieces[W_KNIGHT].loadFromFile("chess/N_W.png");
    pieces[B_KNIGHT].loadFromFile("chess/N_B.png");
    pieces[W_PAWN].loadFromFile("chess/P_W.png");
    pieces[B_PAWN].loadFromFile("chess/P_B.png");

    int n = 0;
    if (color)
    for (int i = 0; i < 8; i++)
    {

         
            for (int j = 0; j < 8; j++) {
                if (start_poss[i][j])
                {

                    pieces_s.push_back(sf::Sprite{});
                    pieces_s[n].setTexture(pieces[start_poss[i][j]]);
                    pieces_s[n].setScale(4 * size / 5 / pieces[start_poss[i][j]].getSize().y, 4 * size / 5 / pieces[start_poss[i][j]].getSize().y);
                    pieces_s[n].setOrigin(pieces[start_poss[i][j]].getSize().x / 2, pieces[start_poss[i][j]].getSize().y / 2);
                    pieces_s[n].setPosition(size * (j + 1) + size / 2, size * (i + 1) + size / 2);
                    if (n == 32) break;
                    n++;
                }
                if (n == 32) break;
            }
      
    }
    else
    for (int i = 0; i <8; i++)
    {


            for (int j = 0; j < 8; j++) {
                if (start_poss[i][j])
                {

                    pieces_s.push_back(sf::Sprite{});
                    pieces_s[n].setTexture(pieces[start_poss[i][j]]);
                    pieces_s[n].setScale(4 * size / 5 / pieces[start_poss[i][j]].getSize().y, 4 * size / 5 / pieces[start_poss[i][j]].getSize().y);
                    pieces_s[n].setOrigin(pieces[start_poss[i][j]].getSize().x / 2, pieces[start_poss[i][j]].getSize().y / 2);
                    pieces_s[n].setPosition(size * (8-j ) + size / 2, size * (8-i) + size / 2);
                    if (n == 32) break;
                    n++;
                }
                if (n == 32) break;
            }

    }


}

GameControler::~GameControler()
{
    
}

void GameControler::Run()
{
 
    /*position.make_move("e2e4");
    position.make_move("e7e5");
    position.make_move("f2f4");
    position.make_move("e5f4");**/
    Position game_pos = position;
    
   
    int level;
    int color;
    try {
        Menu menu{ this->window,this->view };
        menu.run(level, color);
        this->color = static_cast<bool>(color);
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return;
    }
   
    Game game(color, level, output, input, game_pos);
    b1 = std::move(std::unique_ptr<Gameboard> {new Gameboard{ size, size, this->color, size } });
    std::thread game_thread(&Game::run, game);
    int n = 0;
    bool isMove = 0;
    int dx = 0;
    int dy = 0;
    sf::Vector2f prev_pos;
    sf::Vector2f check_pos;
    std::string move;
   
        while (window.isOpen())
        {


            sf::Event event;
            sf::Vector2i pos = sf::Mouse::getPosition(window);
            while (window.pollEvent(event))
            {
                if (position.color() == this->color or event.type == sf::Event::Closed or event.type == sf::Event::Resized)
                    switch (event.type)
                    {

                    case sf::Event::Closed:
                       this->output.push("2");
                       game_thread.join();
                        window.close();
                        return;
                       

                    case sf::Event::MouseButtonPressed:
                        if (event.mouseButton.button == sf::Mouse::Left)
                        {
                            for (int i = 0; i < pieces_s.size(); i++)
                                if (pieces_s[i].getGlobalBounds().contains(pos.x, pos.y))
                                {
                                    if (not isMove)
                                        prev_pos = pieces_s[i].getPosition();
                                    isMove = 1; n = i;
                                    dx = pos.x - pieces_s[i].getPosition().x;
                                    dy = pos.y - pieces_s[i].getPosition().y;

                                }
                        }
                        else if (isMove and event.mouseButton.button == sf::Mouse::Right)
                        {
                            isMove = 0;
                            pieces_s[n].setPosition(prev_pos);
                        }
                        break;
                    case sf::Event::MouseButtonReleased:
                        if (isMove and event.mouseButton.button == sf::Mouse::Left)
                        {
                            isMove = 0;
                            check_pos.x = (((int)pos.x / (int)size) * (int)size + size / 2);
                            check_pos.y = (((int)pos.y / (int)size) * (int)size + size / 2);
                            b1->normal();
                             move = tonot(prev_pos.x, prev_pos.y, check_pos.x, check_pos.y);
                            std::cout << move << std::endl;
                           this->output.push(move);
                            position.make_legal_move(move);

                            draw_from_position(position);
                        }
                        break;
                    case sf::Event::Resized:
                        resize();
                        draw_from_position(position);
                        break;
                    case sf::Event::KeyPressed:
                        if (event.key.code == sf::Keyboard::Space)
                        {

                            this->output.push("1");
                            b1->normal();
                            std::this_thread::yield();
                            std::this_thread::sleep_for(std::chrono::duration<float>{0.30});
                            position = game_pos;
                            b1->highlight(position.last_move());
                            draw_from_position(position);

                        }
                        break;
                   

                    }



                if (isMove)pieces_s[n].setPosition(pos.x - dx, pos.y - dy);
                
                

            }
            move.clear();
            move = input.pop();
            if (not move.empty())
            {
                if (move == "2")
                {
                    std::this_thread::sleep_for(std::chrono::duration<int>{2});
                    game_thread.join();
                    this->color = not this->color;
                    game_pos = position = Position();
                    Game game = Game(this->color, level, output, input, game_pos);
                    game_thread = std::move(std::thread(&Game::run, game));
                    b1 = std::move(std::unique_ptr<Gameboard> {new Gameboard{ size, size, this->color, size } });
                    
                }
                b1->normal();
                b1->highlight(move);
                std::cout << move << std::endl;
                position = game_pos;
                draw_from_position(position);


            }
            draw(n);
        }
    
        if (game_thread.joinable())
        {
            this->output.push("2");
            game_thread.join();
        }
}

std::string GameControler::tonot(float x_st, float y_st, float x_end, float y_end)
{

    char r[5]{};
    if (this->color)
    {
        r[0] = 'a' + static_cast<char> (x_st / size - 1);
        r[1] = '1' + 8 - static_cast<char> (y_st / size);
        r[2] = 'a' + static_cast<char> (x_end / size - 1);
        r[3] = '1' + 8 - static_cast<char> (y_end / size);
    }
    else
    {
        r[0] = 'h' - static_cast<char> (x_st / size - 1);
        r[1] = '0' +  static_cast<char> (y_st / size);
        r[2] = 'h' - static_cast<char> (x_end / size - 1);
        r[3] = '0' +  static_cast<char> (y_end / size);

    }
    r[4] = 0;

     
    return std::string(r);
}


