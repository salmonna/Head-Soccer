#include "power/DuplicateBall.h"
#include "Resources.h"
//--------------------------------------------------------------------------
DuplicateBall::DuplicateBall()
{

	for (int i = 0; i < 3; i++)
	{
		auto sprite = sf::Sprite(Resources::getInstance().getBallTexture()[0]);
		m_ballSprites.push_back(sprite);
	}
	
}
//--------------------------------------------------------------------------
void DuplicateBall::draw(sf::RenderWindow& window, sf::Vector2f position) {


}
//--------------------------------------------------------------------------
void DuplicateBall::activatePower(sf::CircleShape& ball, sf::Vector2f& currVelocity, sf::Vector2f& direction) {


}
//--------------------------------------------------------------------------
DuplicateBall::~DuplicateBall()
{
}