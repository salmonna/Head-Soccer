#pragma once
#include "gameObject/MovingObject.h"
#include <SFML/Graphics.hpp>
#include "Factory/MovingFactory.h"
#include "power/Power.h"
#include "gameObject/Ball.h"
#include "Box2d.h"
#include <iostream>
#include "gameObject/Ball.h"

class ComputerPlayer :public MovingObject
{
public:

	ComputerPlayer();
	
	virtual void move(sf::Vector2f pressed) override;
	virtual void draw(sf::RenderWindow& window)const override;
	virtual sf::Sprite& getSprite() override { return m_sprite; };
	virtual void reset()override;
	virtual b2Body* getBody()const override;

	void movePlayer(sf::Vector2f startPos, int maxSprite, float maxTime);
	void resetToPosition(sf::Vector2f startPos = sf::Vector2f(160, 590), int numOfJump = 0);
	void setBall(std::shared_ptr<Ball> ball);

	virtual ~ComputerPlayer();
private:

	void update();
	void updateMovement(const sf::Vector2f& ballPosition, float length, const sf::Vector2f& direction);
	
	std::shared_ptr<Ball> m_ball;
	std::shared_ptr<Power> m_power;
	std::vector<sf::Vector2f> m_startSprite;

	sf::Clock m_moveClock;
	sf::Vector2f m_basePosition;
	sf::Vector2f m_velocity;
	sf::Sprite m_sprite;

	b2Body* m_body;

	bool m_jump;
	int m_numOfJump;

	static bool m_registeritComputerPlayer;
};

