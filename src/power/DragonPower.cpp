#include "power/DragonPower.h"
#include "Resources.h"
//--------------------------------------------------------------
DragonPower::DragonPower():m_round(0),m_rightSide(false)
{
	m_posDragon.push_back(std::make_pair(sf::Vector2i(84, 41), sf::Vector2i(71, 71)));
	m_posDragon.push_back(std::make_pair(sf::Vector2i(51, 119), sf::Vector2i(138, 77)));
	m_posDragon.push_back(std::make_pair(sf::Vector2i(41, 212), sf::Vector2i(165, 80)));
	m_posDragon.push_back(std::make_pair(sf::Vector2i(11, 314), sf::Vector2i(228, 74)));
	m_posDragon.push_back(std::make_pair(sf::Vector2i(18, 394), sf::Vector2i(228, 74)));
	m_posDragon.push_back(std::make_pair(sf::Vector2i(12, 471), sf::Vector2i(234, 90)));
	m_posDragon.push_back(std::make_pair(sf::Vector2i(14, 561), sf::Vector2i(231, 80)));

	m_dragonSprite.setTexture(Resources::getInstance().getPlayerPower()[0]);
}
//--------------------------------------------------------------
void DragonPower::draw(sf::RenderWindow& window, sf::Vector2f position) {

	if (m_clockDragon.getElapsedTime().asMilliseconds() >= 150.f)
	{
		if (m_round == m_posDragon.size()) {

			m_round = 3;
		}
		dragonRect(m_posDragon[m_round]);
		m_round++;

		m_clockDragon.restart();
	}
	
	if (!m_rightSide) {

		position.x -= (m_dragonSprite.getGlobalBounds().width * 0.9);
		position.y -= (m_dragonSprite.getGlobalBounds().height / 2);
	}
	else
	{
		position.x += (m_dragonSprite.getGlobalBounds().width * 0.9);
		position.y -= (m_dragonSprite.getGlobalBounds().height / 2);
		
	}
	m_dragonSprite.setPosition(position);
	window.draw(m_dragonSprite);
}
//--------------------------------------------------------------
void DragonPower::dragonRect(std::pair<sf::Vector2i, sf::Vector2i> it) {

	sf::IntRect characterRect(it.first.x, it.first.y, it.second.x, it.second.y);
	m_dragonSprite.setTextureRect(characterRect);
	m_dragonSprite.setScale(4, 4);

	if (m_rightSide) {

		m_dragonSprite.scale(-1,1);
	}

}
//--------------------------------------------------------------
void DragonPower::activatePower(sf::CircleShape& ball, sf::Vector2f& currVelocity, sf::Vector2f& direction) {

	currVelocity = sf::Vector2f(1500.f, 0.f);
	currVelocity.x *= direction.x;

	sf::Vector2f currPos = ball.getPosition();
	currPos.y  = 400.f;

	if (direction.x < 0)
	{
		m_rightSide = true;
	}
	

	ball.setPosition(currPos);

	m_round = 0;
}
//--------------------------------------------------------------
DragonPower::~DragonPower()
{
}