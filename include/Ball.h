#pragma once
#include "MovingObject.h"
#include "Window.h"

class Ball : public MovingObject
{
public:
	Ball();

	virtual void draw(sf::RenderWindow& window) override;
	virtual void move(int keyPressed) override;


	~Ball() = default;

private:
	sf::Sprite m_sprite;
	sf::Vector2f m_ballVelocity;

};

