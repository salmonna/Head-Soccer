#pragma once
#include <SFML/Graphics.hpp>



class ScoreBoard
{
public:
	ScoreBoard();
	void draw(sf::RenderWindow& window);


	~ScoreBoard() = default;

private:

	std::vector<sf::Sprite> m_SpriteVec;
};
