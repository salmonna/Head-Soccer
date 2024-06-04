
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Window.h"

#include "ScoreBoard.h"
#include "Goal.h"


class Board
{
public:
	Board(std::vector<sf::Texture>& texturs);

	void respond(sf::Vector2f loc);
	void draw(sf::RenderWindow& window);
	
	bool isOpen() const;

	~Board() = default;

private:

	void timeCalculation();

	bool m_boardOpen;

	ScoreBoard m_scoreBoard;

	sf::Sprite m_backGroundStadium;

	Goal m_leftGoal;
	Goal m_rightGoal;
};



