#pragma once
#include "gameObject/MovingObject.h"
#include <SFML/Graphics.hpp>
#include "Factory/MovingFactory.h"
#include "power/Power.h"


class ComputerPlayer :public MovingObject
{
public:

	ComputerPlayer();
	
	virtual void move(sf::Vector2f pressed) override;
	void checkBallPosition(sf::Vector2f& ballPosition);
	virtual void draw(sf::RenderWindow& window)const override;
	virtual sf::Sprite& getSprite() override { return m_sprite; };
	virtual sf::Vector2f getPosition() const { return m_sprite.getPosition(); };
	virtual void reset()override;

	void movePlayer(sf::Vector2f startPos, int maxSprite, float maxTime);
	void resetToPosition(sf::Vector2f startPos, int numOfJump, int posX, int posY);

	sf::Vector2f getRivalGoal()const;

	void updateGravityAndCollision();
	void moveWithRange(int x);

	virtual ~ComputerPlayer();


private:

	int m_numOfJump;
	int m_posX;
	int m_posY;
	int m_move;
	int m_gravity;
	sf::Clock m_moveClock;
	std::unique_ptr<Power> m_power;
	std::vector<sf::Vector2f> m_startSprite;

	sf::Vector2f m_basePosition;

	sf::Vector2f m_velocity;
	sf::Sprite m_sprite;

	sf::Vector2f m_rivalGoal;

	static bool m_registeritComputerPlayer;

};

