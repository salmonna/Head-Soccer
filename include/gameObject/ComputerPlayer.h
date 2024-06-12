#pragma once
#include "gameObject/MovingObject.h"
#include <SFML/Graphics.hpp>


class ComputerPlayer :public MovingObject
{
public:

	ComputerPlayer();
	
	
	virtual void move(sf::Vector2f pressed) override {};
	virtual void draw(sf::RenderWindow& window)const override;

	virtual sf::Sprite& getSprite() override { return m_sprite; };

	virtual sf::Vector2f getPosition() const { return m_sprite.getPosition(); };

	void movePlayer(sf::Vector2f startPos, int maxSprite, float maxTime);
	void resetToPosition(sf::Vector2f startPos, int numOfJump, int posX, int posY);

	void updateComputerPlayer(/*sf::RectangleShape& player, sf::Vector2f& ballvelocity,*/ sf::CircleShape& ball
							 /*sf::RectangleShape& userGoal  float deltaTime*/);

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

	std::vector<sf::Vector2f> m_startSprite;

	sf::Vector2f m_basePosition;

	sf::Vector2f m_velocity;
	sf::Sprite m_sprite;

	
};

