
#pragma once
#include "MovingObject.h"
#include "Window.h"
#include <SFML/Graphics.hpp>
#include "Factory/MovingFactory.h"
#include <memory>
#include "power/MoveBehavior.h"
#include "power/RegularBehavior.h"
#include "power/Power.h"
#include "Box2d.h"
#include <iostream>


class Ball : public MovingObject
{
public:
	Ball();

	virtual void draw(sf::RenderWindow& window) const override;
	virtual void move() override;
	virtual sf::Sprite& getSprite() override;
	virtual void reset() override;
	virtual b2Body* getBody()const override;

	void update();
	void kick(bool rigthSide);

	//----------------------- get --------------//
	sf::Color getBallColor()const;
	std::shared_ptr<Power> getPower()const;
	b2MassData getBallMass() const;

	//----------------------- set --------------//
	void setPosition(sf::Vector2f position);
	void setPower(std::shared_ptr<Power> power);

	virtual ~Ball();
private:

	void updatePowerState();

	sf::Vector2f m_basePosition;
	sf::Color m_ballColor;
	sf::Sprite m_sprite;
	
	std::shared_ptr<Power> m_power;
	
	b2Body* m_body;
	b2MassData m_bodyMass;

	bool m_restartBall;
	
	static bool m_registeritBall;

	float m_gravityScale;
};