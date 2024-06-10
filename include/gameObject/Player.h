
#pragma once
#include "MovingObject.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "Keyboard.h"


class Player: public MovingObject
{
public:
	Player(bool right, Keyboard keys);

	virtual void draw(sf::RenderWindow& window) const override;
	virtual void move(sf::Vector2f pressed) override;

	virtual  sf::Vector2f getPosition() const override;

	virtual sf::Sprite& getSprite() override;

	virtual int getKeypressed() override;

	Keyboard getKey() const;

	virtual ~Player() = default;
private:

	int m_numOfJump;
	int m_posX;
	int m_posY;
	int m_move;
	int m_gravity;

	bool m_movePlayer;
	bool m_playerSide;
	bool m_moveDown;

	sf::Sprite m_sprite;
	sf::Clock m_moveClock;

	std::vector<sf::Vector2f> m_startSprite;


	Keyboard m_keys;

	void movePlayer(sf::Vector2f startPos, int maxSprite, float maxTime);
	bool keyPressedValid(int keyPressed);
};
