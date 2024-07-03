#include "MovePlayerState/BaseMovePlayerState.h"
#include "Resources.h"
//-----------------------------------------------------------------------------------------------------
BaseMovePlayerState::BaseMovePlayerState() :m_numOfJump(0)
{
}
//-----------------------------------------------------------------------------------------------------
void BaseMovePlayerState::movePlayer(sf::Vector2f startPos,int maxSprite, float maxTime, sf::Sprite& sprite, sf::Vector2f size) {

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
			resetToPosition(sprite,startPos,m_numOfJump, size);
		}
	}
}
//-----------------------------------------------------------------------------------------------------
// Reset to default position if not jumping
void BaseMovePlayerState::resetToPosition(sf::Sprite& sprite, sf::Vector2f startPos, int numOfJump, sf::Vector2f size) {

	sf::IntRect characterRect(int(startPos.x) + numOfJump, int(startPos.y), int(size.x), int(size.y)); // Assuming each character is 32x32 pixels
	// Set the texture rectangle to the character's position and size on the sprite sheet
	sprite.setTextureRect(characterRect);
}
//-----------------------------------------------------------------------------------------------------
bool BaseMovePlayerState::changeState(int maxSprite)const {

	return m_numOfJump > 110 * maxSprite;
}
//-----------------------------------------------------------------------------------------------------
BaseMovePlayerState::~BaseMovePlayerState()
{

}