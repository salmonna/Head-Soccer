#pragma once
#include "gameObject/MovingObject.h"
#include <SFML/Graphics.hpp>
#include "Factory/MovingFactory.h"
#include "power/Power.h"
#include "gameObject/Ball.h"
#include "Box2d.h"
#include <iostream>

class ComputerPlayer :public MovingObject
{
public:

	ComputerPlayer();
	
	virtual void move(sf::Vector2f pressed) override;
	virtual void draw(sf::RenderWindow& window)const override;
	virtual sf::Sprite& getSprite() override { return m_sprite; };
	virtual sf::Vector2f getPosition() const { return m_sprite.getPosition(); };
	virtual void reset()override;

	void movePlayer(sf::Vector2f startPos, int maxSprite, float maxTime);
	void resetToPosition(sf::Vector2f startPos = sf::Vector2f(160, 590), int numOfJump = 0);

	sf::Vector2f getRivalGoal()const;

	virtual ~ComputerPlayer();


private:

	void update();

	int m_numOfJump;

	sf::Clock m_moveClock;
	std::unique_ptr<Power> m_power;
	std::vector<sf::Vector2f> m_startSprite;

	sf::Vector2f m_basePosition;

	sf::Vector2f m_velocity;
	sf::Sprite m_sprite;

	sf::Vector2f m_rivalGoal;

	static bool m_registeritComputerPlayer;

	b2Body* m_body;
	bool m_jump;
};

