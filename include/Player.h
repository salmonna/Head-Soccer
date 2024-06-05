
#pragma once
#include "MovingObject.h"
#include <SFML/Graphics.hpp>
#include <vector>

enum UserPressed
{
	SPACE = 57, LEFT = 71, RIGHT = 72, JUMP = 73, DOWN = -1, SLIDE = 74
};


class Player: public MovingObject
{
public:
	Player(sf::Texture& texture);

	virtual void draw(sf::RenderWindow& window) override;

	virtual void move(int keyPressed) override;

	~Player() = default;
private:

	int m_jump;
	int m_posX;
	int m_posY;
	int m_move;

	bool m_movePlayer;

	sf::Sprite m_sprite;
	sf::Clock m_moveClock;

	std::vector<sf::Vector2f> m_startSprite;

	void movePlayer(sf::Vector2f startPos, int jump);
};
