#include "Field.h"




Field::Field(float x, float y, bool color, float size)
{
	this->color = color;
	shape.setPosition(x, y);
	shape.setSize(sf::Vector2f(size, size));
	color ? shape.setFillColor(sf::Color(250, 225, 215,255)) : shape.setFillColor(sf::Color(150, 55, 35,199));//(255,230,230,240) (108,170,76,190)
}

Field::~Field()
{
}

void Field::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
   
	target.draw(this->shape);
}

void Field::resize(float x, float y, float size)
{
	shape.setPosition(x, y);
	shape.setSize(sf::Vector2f(size, size));
}

void Field::highlight()
{
	this->color ? shape.setFillColor(sf::Color(250, 100, 100, 255)) : shape.setFillColor(sf::Color(200, 75, 75, 250));
}

void Field::normal()
{
	this->color ? shape.setFillColor(sf::Color(250, 225, 215, 255)) : shape.setFillColor(sf::Color(150, 55, 35, 199));
}





