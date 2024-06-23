#pragma once
#include <SFML/Graphics.hpp>
#include "Box2d.h"

class BaseMovePlayerState
{
public:
	BaseMovePlayerState();
	virtual ~BaseMovePlayerState() ;

	virtual void movement(sf::Sprite& sprite, sf::Vector2i& pos, sf::Vector2f basePos, int& gravity, bool playerSide, b2Body* m_body) = 0;
	virtual BaseMovePlayerState* handleMoveStatus() = 0;

	void movePlayer(sf::Vector2f startPos, int maxSprite, float maxTime, sf::Sprite& sprite, sf::Vector2i& pos , sf::Vector2f basePos);
	void moveWithRange(int x, sf::Vector2i& pos, bool playerSide);
	void resetToPosition(sf::Sprite& sprite, sf::Vector2i& pos, sf::Vector2f basePos, sf::Vector2f startPos = sf::Vector2f(160, 590), int numOfJump = 0);

	bool changeState(int maxSprite);

private:

	sf::Clock m_moveClock;

	int m_numOfJump; 

	
};

