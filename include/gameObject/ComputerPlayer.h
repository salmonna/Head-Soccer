#pragma once
#include "gameObject/MovingObject.h"
#include <SFML/Graphics.hpp>


class ComputerPlayer :public MovingObject
{
public:

	ComputerPlayer();
	
	
	virtual void move(sf::Vector2f pressed) override {};
	virtual void draw(sf::RenderWindow& window)const override{};

	void movePlayer(sf::Vector2f startPos, int maxSprite, float maxTime);
	void resetToPosition(sf::Vector2f startPos, int numOfJump, int posX, int posY);

	void updateComputerPlayer(/*sf::RectangleShape& player, sf::Vector2f& ballvelocity,*/ sf::CircleShape& ball
							 /*sf::RectangleShape& userGoal  float deltaTime*/);

	~ComputerPlayer();

private:

	int m_numOfJump;
	int m_posX;
	int m_posY;
	int m_move;
	sf::Clock m_moveClock;

	sf::Vector2f m_basePosition;

	sf::Vector2f m_velocity;
	sf::Sprite m_sprite;

	
};

