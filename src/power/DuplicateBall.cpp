#include "power/DuplicateBall.h"
#include "Resources.h"
//--------------------------------------------------------------------------
DuplicateBall::DuplicateBall(): m_isIntiliaz(true)
{

	for (int i = 0; i < 3; i++)
	{
		auto sprite = sf::Sprite(Resources::getInstance().getBallTexture()[0]);
		m_ballSprites.push_back(sprite);
	}
	m_velocity = 0;
}
//--------------------------------------------------------------------------
void DuplicateBall::resetPos(sf::Vector2f& position)
{
	int j = 1;
	for (int i = 0; i < m_ballSprites.size(); i++)
	{
		m_ballSprites[i].setPosition(position.x, position.y - (50 * (i + 2) * j));

		j = j * -1;
	}
}
//--------------------------------------------------------------------------
void DuplicateBall::activatePowerOnBall(Ball* ball) {

	//currVelocity = sf::Vector2f(1500.f, 0.f);
	//currVelocity.x *= direction.x;

	//sf::Vector2f currPos = ball.getPosition();
	//currPos.y = 400.f;

	//ball.setPosition(currPos);

	//m_direction = direction;
	//m_isIntiliaz = true;
}
//--------------------------------------------------------------------------
DuplicateBall::~DuplicateBall()
{
}