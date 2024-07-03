#include "power/DragonPower.h"
#include "Resources.h"
#include "gameObject/Ball.h"
#include "gameObject/Player.h"

//--------------------------------------------------------------
DragonPower::DragonPower(bool PlayerSide):m_round(0),m_PlayerSide(PlayerSide),m_startPos(true)
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
void DragonPower::activatePowerOnBall(Ball* ball) {
	
	setPowerIsActive(true);

	b2Vec2 currentPosition = ball->getBody()->GetPosition();
	currentPosition.y -= 3.f; // Move the body 200 pixels higher (adjust as needed)
	ball->getBody()->SetTransform(currentPosition, ball->getBody()->GetAngle());

	//set gravity
	ball->getBody()->SetGravityScale(0.0f);
	b2Vec2 velocity(5.0f, 0.0f);
	ball->getBody()->SetLinearVelocity(velocity);

	// Set awake state to false to "pause" the body
	ball->getBody()->SetAwake(false);
}
//--------------------------------------------------------------
void DragonPower::activatePowerOnPlayer(Player* Player) {

	Player->setPowerOnPlayer(true);
	setPowerIsActive(false);
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
	
	defineStartposWithBall(position);
	
	m_dragonSprite.setPosition(position);

	window.draw(m_dragonSprite);
}
//--------------------------------------------------------------
void DragonPower::defineStartposWithBall(sf::Vector2f & position) {

	if (!m_PlayerSide) {

		position.x -= (m_dragonSprite.getGlobalBounds().width * 0.9);
		position.y -= (m_dragonSprite.getGlobalBounds().height / 2);
	}
	else
	{
		position.x += (m_dragonSprite.getGlobalBounds().width * 0.9);
		position.y -= (m_dragonSprite.getGlobalBounds().height / 2);

	}
}
//--------------------------------------------------------------
void DragonPower::dragonRect(std::pair<sf::Vector2i, sf::Vector2i> it) {

	sf::IntRect characterRect(it.first.x, it.first.y, it.second.x, it.second.y);
	m_dragonSprite.setTextureRect(characterRect);
	m_dragonSprite.setScale(4, 4);

	if (m_PlayerSide) {

		m_dragonSprite.scale(-1,1);
	}

}


bool DragonPower::getSideOfPlayer()const {
	return m_PlayerSide;
}
//--------------------------------------------------------------
DragonPower::~DragonPower()
{
}