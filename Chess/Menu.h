#pragma once
#include <vector>
#include<SFML/Graphics.hpp>
#include"Button.h"
class Button;
class Menu
{
	sf::RenderWindow *window; sf::View view;
	void resize();
	sf::Text text;
public:
	void run(int &level, int &color);
	std::vector<Button> buttons;
	Menu(sf::RenderWindow &window, sf::View view);
};

