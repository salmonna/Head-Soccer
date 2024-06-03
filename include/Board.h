
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Window.h"
#include "Goal.h"
#include "RightGoal.h"

class Board
{
public:
	Board(std::vector<sf::Texture>& texturs);

	void respond(sf::Vector2f loc);
	void draw(sf::RenderWindow& window);
	
	bool isOpen() const;

	~Board() = default;

private:


	bool m_boardOpen;

	sf::Sprite m_backGroundStadium;
	Goal m_goal;
	RightGoal m_rightGoal;
	
};



