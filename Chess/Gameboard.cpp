#include "Gameboard.h"
#include "Field.h"
Gameboard::Gameboard(float x, float y, bool player, float size)
{
	this->player = player ;
	for (int i = 0; i < 8; i++) {
		board.push_back(std::vector<Field>());
		for (int j = 0; j < 8; j++)
		{
			board[i].push_back(Field{ size * static_cast<float>(i) + x, size * static_cast<float>(j) + y ,static_cast<bool> ((i + j + player) % 2),size });
		}
	}


}

Gameboard::~Gameboard()
{

}

void Gameboard::draw(sf::RenderTarget& target, sf::RenderStates state) const
{

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			this->board[i][j].draw(target, state);

		}

}

void Gameboard::resize(float size)
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			this->board[i][j].resize(size * static_cast<float>(i) + size, size * static_cast<float>(j) + size, size);

		}
}

void Gameboard::highlight(std::string move)
{ 
	if (move.size() >= 4 and move != "0000")
	{
		
		char y1 = static_cast<char>(move[0] - 'a');
		char x1 = 7 - static_cast<char>(move[1] - '1');
		char y2 = static_cast<char>(move[2] - 'a');
		char x2 = 7 - static_cast<char>(move[3] - '1');
		if (player) {
			this->board[y1][x1].highlight();
			this->board[y2][x2].highlight();
		}
		else
		{
			this->board[7-y1][7 - x1].highlight();
			this->board[7 - y2][7 - x2].highlight();
		}
	}
	
}

void Gameboard::normal()
{
	
		
	for (auto i = this->board.begin(); i != this->board.end(); i++)
	{
		for (auto j = (*i).begin(); j != (*i).end(); j++)
		{
			j->normal();
		}
	}
		
	
}
