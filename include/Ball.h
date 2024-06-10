

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
	virtual  sf::Vector2f  getPosition() const override;
	virtual sf::Sprite& getSprite() override;
	sf::Vector2f getVelocity() const;

	void setPosition(sf::Vector2f position);
	void setBallVelocity(sf::Vector2f velocity);
	float getRadius() const;

	virtual ~Ball() = default;

private:


	sf::Sprite m_sprite;
	sf::CircleShape m_ball;



	sf::Vector2f m_ballVelocity;

	sf::Clock m_clock;
};

