#pragma once
#include <SFML/Graphics.hpp>
#include "Box2d.h"

class BaseMovePlayerState
{
public:
	BaseMovePlayerState();
	
	virtual void movement(sf::Sprite& sprite, bool playerSide, b2Body* body) = 0;
	virtual BaseMovePlayerState* handleMoveStatus() = 0;

	void movePlayer(sf::Vector2f startPos, int maxSprite, float maxTime, sf::Sprite& sprite, sf::Vector2f size);
	void resetToPosition(sf::Sprite& sprite, sf::Vector2f startPos = sf::Vector2f(160, 590), int numOfJump = 0, sf::Vector2f size = sf::Vector2f(60, 85));
	bool changeState(int maxSprite)const;
	
	virtual ~BaseMovePlayerState();
private:

	sf::Clock m_moveClock;

	int m_numOfJump; 

	
};

