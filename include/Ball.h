

#pragma once
#include "MovingObject.h"
#include "Window.h"
#include <SFML/Graphics.hpp>

class Ball : public MovingObject
{
public:
	Ball();

	virtual void draw(sf::RenderWindow& window) override;
	virtual void move(int keyPressed) override;
	virtual int getKeypressed() override;

	virtual sf::Sprite& getSprite() { return m_sprite; };


	virtual ~Ball() = default;

private:
	int m_keyPressed;

	sf::Sprite m_sprite;

	sf::CircleShape m_ball;

	sf::Vector2f m_ballVelocity;

	sf::Clock m_clock;
};

