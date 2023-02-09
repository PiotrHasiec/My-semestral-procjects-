#pragma once
#include <SFML/Graphics.hpp>
class Button
	:public sf::Drawable
{
	sf::RectangleShape shape;
	bool pressed =  0;
	int (*function)(int&, int&);
	sf::Color if_pressed;
	sf::Color normal;
	float size_x;
	float size_y;
	float x;
	float y;
	float scale;
	sf::Text text;
public:
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
	Button(int function(int&, int&),  sf::Color if_pressed, sf::Color normal, float x, float y, float size_x, float size_y, sf::Text text );
	int press(int& level, int& color);
	void resize(float size);
	void release();
	sf::RectangleShape get_shape();
};

