

#pragma once
#include "MovingObject.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Player: public MovingObject
{
public:
	Player(sf::Texture& texture);

	void draw(sf::RenderWindow& window) override;

	void move(int keyPressed) override;


private:

	int m_jump;
	int m_pos;
	int m_move;

	bool m_movePlayer;

	sf::Sprite m_sprite;
	sf::Clock m_moveClock;

	std::vector<sf::Vector2f> m_startSprite;

	void movePlayer(sf::Vector2f startPos, int jump);
	void moveLeft();
};

