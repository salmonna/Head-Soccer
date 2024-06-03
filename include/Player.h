

#pragma once
#include "MovingObject.h"


class Player: public MovingObject
{
public:
	Player(sf::Texture& texture);

	void draw(sf::RenderWindow& window);

	void move(int keyPressed);

	~Player();

private:

	int m_jump;
	int m_pos;

	bool m_movePlayer;

	sf::Sprite m_sprite;
	sf::Clock m_moveClock;
};

