
#pragma once
#include "MovingObject.h"
#include "Window.h"
#include <SFML/Graphics.hpp>
#include "Factory/MovingFactory.h"

class Ball : public MovingObject
{
public:
	Ball();

	virtual void draw(sf::RenderWindow& window) const override;
	virtual void move(sf::Vector2f pressed) override;
	virtual sf::Vector2f getPosition() const override;
	virtual sf::Sprite& getSprite() override;
	virtual void reset()override;

	sf::Vector2f getVelocity() const;
	void setPosition(sf::Vector2f position);
	void setBallVelocity(sf::Vector2f velocity);
	float getRadius() const;

	void restartBall();

	virtual ~Ball() = default;


	//just for chacking --------
	sf::CircleShape& getCircle();
	//--------------------------
private:


	sf::Sprite m_sprite;
	sf::CircleShape m_ball;

	sf::Vector2f m_ballVelocity;

	sf::Clock m_clock;
	static bool m_registeritBall;
};