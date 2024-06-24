#include "MovePlayerState/BaseMovePlayerState.h"
#include "Resources.h"
//-----------------------------------------------------------------------------------------------------
BaseMovePlayerState::BaseMovePlayerState() :m_numOfJump(0)
{

	/*m_startSprite.push_back(sf::Vector2f(160, 126));
	m_startSprite.push_back(sf::Vector2f(160, 244));
	m_startSprite.push_back(sf::Vector2f(160, 8));
	m_startSprite.push_back(sf::Vector2f(160, 365));*/
}
//-----------------------------------------------------------------------------------------------------
void BaseMovePlayerState::movePlayer(sf::Vector2f startPos,int maxSprite, float maxTime, sf::Sprite& sprite, sf::Vector2i& pos , sf::Vector2f basePos) {

	float sec = float(m_moveClock.getElapsedTime().asMilliseconds());
	if (maxTime < sec)
	{
		if (changeState(maxSprite))
		{
			m_numOfJump = 0;
			return;
		}
		else
		{
			m_moveClock.restart();
			m_numOfJump += 115;
			resetToPosition(sprite, pos, basePos,startPos,m_numOfJump);
		}
	}

}
//-----------------------------------------------------------------------------------------------------
bool BaseMovePlayerState::changeState(int maxSprite) {

	return m_numOfJump > 110 * maxSprite;
}
//-----------------------------------------------------------------------------------------------------
// Reset to default position if not jumping
void BaseMovePlayerState::resetToPosition(sf::Sprite& sprite, sf::Vector2i& pos,sf::Vector2f basePos,sf::Vector2f startPos, int numOfJump) {

	sf::IntRect characterRect(startPos.x + numOfJump, startPos.y, 80, 90); // Assuming each character is 32x32 pixels
	// Set the texture rectangle to the character's position and size on the sprite sheet
	sprite.setTextureRect(characterRect);
	sprite.setPosition(float(basePos.x + pos.x), float(basePos.y + pos.y));
}

//-----------------------------------------------------------------------------------------------------
void BaseMovePlayerState::moveWithRange(int x, sf::Vector2i & pos, bool playerSide) {

	if (playerSide)
	{
		if (pos.x + x > -1400 && pos.x + x < 220)
			pos.x += x;
	}
	else
	{
		if (pos.x + x > -220 && pos.x + x < 1400)
			pos.x += x;
	}
}
//-----------------------------------------------------------------------------------------------------
BaseMovePlayerState::~BaseMovePlayerState()
{

}