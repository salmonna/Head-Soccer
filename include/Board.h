
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Window.h"

class Board
{
public:
	Board(std::vector<sf::Texture>& texturs);

	void respond(sf::Vector2f loc);
	void draw(sf::RenderWindow& window);
	
	bool isOpen() const;

	~Board() = default;

private:

	int m_jump;
	int m_pos;

	bool m_boardOpen;
	std::vector<sf::Sprite> m_vecSprits;

	sf::Clock m_moveClock;
};



