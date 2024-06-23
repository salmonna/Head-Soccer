
#pragma once
#include "MovingObject.h"
#include "Window.h"
#include <SFML/Graphics.hpp>
#include "Factory/MovingFactory.h"
#include <memory>
#include "power/MoveBehavior.h"
#include "power/RegularBehavior.h"
#include "power/Power.h"

class Ball : public MovingObject
{
public:
	Ball();

	virtual void draw(sf::RenderWindow& window) const override;
	void setRegular();
	virtual void move(sf::Vector2f pressed) override;
	virtual sf::Vector2f getPosition() const override;
	virtual sf::Sprite& getSprite() override;
	virtual void reset() override;

	sf::Vector2f getVelocity() const;
	void setPosition(sf::Vector2f position);
	void setBallVelocity(sf::Vector2f velocity);
	float getRadius() const;

	void restartBall();
	sf::Clock& getClock();

	void setMoveBehavior(std::shared_ptr<Power> power);
	bool isRegularBehavior();

	virtual ~Ball() { };


	//just for chacking --------
	sf::CircleShape& getCircle();
	//--------------------------
private:

	std::shared_ptr<Power> m_power;

	sf::Sprite m_sprite;
	sf::CircleShape m_ball;
	sf::Vector2f m_ballVelocity;
	sf::Clock m_clock;
	static bool m_registeritBall;
};