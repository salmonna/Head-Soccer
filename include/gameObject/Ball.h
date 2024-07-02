
#pragma once
#include "MovingObject.h"
#include "Window.h"
#include <SFML/Graphics.hpp>
#include "Factory/MovingFactory.h"
#include <memory>
#include "power/Power.h"
#include "Box2d.h"
#include <iostream>


class Ball : public MovingObject
{
public:
	Ball();

	virtual void draw(sf::RenderWindow& window) const override;
	virtual void move(sf::Vector2f pressed) override;
	virtual sf::Sprite& getSprite() override;
	virtual void reset() override;
	virtual b2Body* getBody()override;

	b2MassData getBallMass() const;
	void setPosition(sf::Vector2f position);
	void setPower(std::shared_ptr<Power> power);
	void update();
	void kick(bool rigthSide);
	sf::Color getBallColor()const;
	std::shared_ptr<Power> getPower();

	virtual ~Ball() {
		std::cout << " B-D" << std::endl;
		m_body->DestroyFixture(m_body->GetFixtureList());
		auto world = Box2d::getInstance().getBox2dWorld();
		world->DestroyBody(m_body);
		m_body = nullptr;
	};
private:
	b2MassData m_bodyMass;
	sf::Vector2f m_basePosition;
	std::shared_ptr<Power> m_power;
	sf::Sprite m_sprite;
	static bool m_registeritBall;
	b2Body* m_body;
	sf::Color m_ballColor;
	bool m_restartBall;
};