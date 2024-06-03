
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Window.h"
#include "MovingObject.h"

class Board
{
public:
	Board(std::vector<sf::Texture>& texturs);

	void respond(int keyPressed);
	void draw(sf::RenderWindow& window);
	
	bool isOpen() const;

	~Board() = default;

private:

	int m_jump;
	int m_pos;

	std::vector<std::unique_ptr<MovingObject>> m_movingObject;

	bool m_boardOpen;
	std::vector<sf::Sprite> m_vecSprits;

	sf::Clock m_moveClock;
};



