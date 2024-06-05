
#pragma once
#include "MovingObject.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "Keyboard.h"


class Player: public MovingObject
{
public:
	Player(sf::Texture& texture, bool right, Keyboard keys);

	virtual void draw(sf::RenderWindow& window) override;

	virtual void move(int keyPressed) override;

	virtual sf::Sprite& getSprite() override;

	virtual ~Player() = default;
private:

	int m_numOfJump;
	int m_posX;
	int m_posY;
	int m_move;

	bool m_movePlayer;
	bool m_playerSide;

	sf::Sprite m_sprite;
	sf::Clock m_moveClock;

	std::vector<sf::Vector2f> m_startSprite;

	Keyboard m_keys;

	void movePlayer(sf::Vector2f startPos, int jump);
	bool keyPressedValid(int keyPressed);
};
