#pragma once
#include <SFML/Graphics.hpp>

class BaseMovePlayerState
{
public:
	BaseMovePlayerState();
	virtual ~BaseMovePlayerState() ;

	virtual void movement(sf::Sprite& sprite, sf::Vector2i& pos, sf::Vector2f basePos, int& gravity, bool playerSide) = 0;
	virtual BaseMovePlayerState* handleMoveStatus() = 0;

	void movePlayer(sf::Vector2f startPos, int maxSprite, float maxTime, sf::Sprite& sprite, sf::Vector2i& pos , sf::Vector2f basePos);
	void moveWithRange(int x, sf::Vector2i& pos, bool playerSide);
	void resetToPosition(sf::Sprite& sprite, sf::Vector2i& pos, sf::Vector2f basePos, sf::Vector2f startPos = sf::Vector2f(160, 590), int numOfJump = 0);
	void updateGravityAndCollision(sf::Sprite& sprite, sf::Vector2f basePos, sf::Vector2i pos, int& gravity);

	bool changeState(int maxSprite);

private:

	
	bool m_playerSide;


	sf::Clock m_moveClock;

	int m_numOfJump; 

	
};

