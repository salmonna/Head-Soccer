
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Window.h"
#include "Goal.h"
#include "RightGoal.h"
#include <memory>

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
	std::vector<std::unique_ptr<Goal>> m_goalObjects;
	
};



