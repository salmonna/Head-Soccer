
#pragma once
#include "MovingObject.h"
#include "Window.h"
#include <SFML/Graphics.hpp>
#include "Factory/MovingFactory.h"
#include "Box2d.h"
#include <iostream>

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
	void update();
	void kick(bool rigthSide);

	virtual ~Ball() {
		std::cout << " B-D" << std::endl;
		m_body->DestroyFixture(m_body->GetFixtureList());
		auto world = Box2d::getInstance().getBox2dWorld();
		world->DestroyBody(m_body);
		m_body = nullptr;
	};

	//just for chacking --------
	sf::CircleShape& getCircle();
	//--------------------------
private:


	sf::Sprite m_sprite;
	sf::CircleShape m_ball;

	sf::Vector2f m_ballVelocity;

	sf::Clock m_clock;
	static bool m_registeritBall;
	b2Body* m_body;
};