#include "Menu.h"
#include "Button.h"
#include "SFML/Graphics.hpp"


void Menu::resize()
{
    float size = window->getSize().y / 10;
    window->setSize(sf::Vector2u(10 * size, 10 * size));
    view.setSize(10 * size, 10 * size);
    view.setCenter(5 * size, 5 * size);
    window->setView(view);
    for (auto i = this->buttons.begin(); i != buttons.end(); i++)
    {
        (*i).resize(size);
    }
}

void Menu::run(int& level, int& color )
{
    float size = window->getSize().y / 10;
    float center = window->getSize().y / 2;
    color = 1;
    level = 3;
    sf::Font font;
    if (!font.loadFromFile("C:/WINDOWS/FONTS/arial.ttf"))
    {
        throw std::exception{ "Nie uda³o siê za³adowaæ czcionki" };
    }
    this->text = sf::Text(sf::String{ "SZACHY" }, font, 100);
    this->buttons.push_back(Button{ []( int& level,int& color) {level = 2; return 0; },sf::Color(15,15,15,200),sf::Color(90, 160, 66, 210),center,center+90,80.0f,180.0f,sf::Text(sf::String{ "Poziom 1" }, font, 100) });
    this->buttons.push_back(Button{ [](int& level,int& color) {level = 3; return 0; },sf::Color(15,15,15,200),sf::Color(90, 160, 66, 210),center,center+180, 80.0f,180.0f,sf::Text(sf::String{ "Poziom 2" }, font, 100) });
    this->buttons.push_back(Button{ [](int& level,int& color) {level = 4; return 0; },sf::Color(15,15,15,200),sf::Color(90, 160, 66, 210),center,center+270,80.0f,180.0f,sf::Text(sf::String{ "Poziom 3" }, font, 100) });
    this->buttons.push_back(Button{ [](int& level,int& color) { return 1; },sf::Color(15,15,15,200),sf::Color(90, 160, 66, 210),center,center,80.0f,180.0f,sf::Text(sf::String{ "Graj" }, font, 100)  });

    
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color(108, 170, 76, 190));
    text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
    text.setPosition(window->getSize().x/2 ,  window->getSize().y / 6);


       
      
    while (window->isOpen())
    {


        sf::Event event;
        sf::Vector2i pos = sf::Mouse::getPosition(*window);
        while (window->pollEvent(event))
        {

            switch (event.type)
            {

            case sf::Event::Closed:

                window->close();
                return;
                break;

            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    for (int i = 0; i < buttons.size(); i++)
                        if (buttons[i].get_shape().getGlobalBounds().contains(pos.x, pos.y))
                        {
                            
                            for (int i = 0; i < buttons.size(); i++)
                                buttons[i].release();
                            if (buttons[i].press(level, color))
                                return;
                        }
                }

                break;

            case sf::Event::Resized:
                window->setSize(sf::Vector2u(10 * size, 10 * size));

                break;
            
          


            }




        }

        window->clear(sf::Color(46, 46, 46, 255));
        
        for (auto i = buttons.begin(); i != buttons.end(); i++)
        {
           window->draw((*i));
        }
        window->draw(this->text);
        window->display();
    }
}

Menu::Menu(sf::RenderWindow &window, sf::View view)
{
   this->window = &window;
   this-> view = view;
   
}

