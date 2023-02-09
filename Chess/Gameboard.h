#pragma once
#include <SFML/Graphics.hpp>
class Field;
class Gameboard :
	public sf::Drawable
{
	std::vector< std::vector<Field> > board;
	bool player;
public:
	Gameboard(float x, float y, bool player, float size);
	~Gameboard();
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
	void resize(float size);
	void highlight(std::string move);
	void normal();
};
