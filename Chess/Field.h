#pragma once
#include <SFML/Graphics.hpp>

#include <vector>

class Gameboard;
class Field :
	public sf::Drawable	
{
	bool color;
	friend class Gameboard;
	sf::RectangleShape shape;
public:
	Field(float x, float y, bool color,float size);

	~Field();
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
	void resize(float x, float y, float size);
	void highlight();
	void normal();
};


