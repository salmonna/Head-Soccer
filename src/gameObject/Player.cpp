
#pragma once
#include "gameObject/Player.h"
#include <iostream>
#include "Resources.h"
#include "gameObject/scoreBoard.h"
#include "power/FirePower.h"
#include "power/InvisiblePower.h"
#include "power/DragonPower.h"
#include "power/DuplicateBall.h"
#include "power/BigBallPower.h"
#include "power/TornadoPower.h"
//#include "power/KameHameHaPower.h"
#include "power/ElectricPower.h"


//-----------------------------------------------------------------------------
Player::Player(bool right, Keyboard keys) :m_numOfJump(0), m_posX(0), m_posY(0), m_move(-2), m_gravity(0),m_keys(keys), m_playerSide(right)
, m_aura(false), m_standMoveState(&m_leftMoveState, &m_rightMoveState,&m_jumpMoveState,&m_kickMoveState), m_leftMoveState(&m_standMoveState, &m_jumpMoveState)
,m_jumpMoveState(&m_standMoveState,&m_kickMoveState), m_kickMoveState(&m_standMoveState,&m_jumpMoveState), m_rightMoveState(&m_standMoveState, &m_jumpMoveState),
m_currentMoveState(&m_standMoveState),m_powerClock(), m_powerClock2(),m_powerOnPlayer(false)
{

	m_sound.setBuffer(Resources::getInstance().getBufferVec()[0]);
	m_power = std::make_shared<DragonPower>(m_playerSide);

	if (m_playerSide)
	{
		m_sprite.setScale(-1, 1);
		m_basePosition = sf::Vector2f(1520, 775);
	}
	else
	{
		m_basePosition = sf::Vector2f(272, 775);
	}
	//----------------------box2d---------------------------//
	m_body = Box2d::getInstance().createPlayer(m_basePosition);

	m_sprite.setOrigin(40.f, 40.f);
	m_sprite.setTexture(Resources::getInstance().getCharactersTexture());
	resetToPosition();
	m_playerColor = m_sprite.getColor();
	m_sprite.setPosition(m_basePosition);

}

bool Player::m_registeritRightPlayer = MovingFactory::registeritMoving("RightPlayer",
	[]() -> std::shared_ptr<MovingObject> { return std::make_shared<Player>(true,
		Keyboard(sf::Keyboard::Space, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Down)); });

bool Player::m_registeritLeftPlayer = MovingFactory::registeritMoving("LeftPlayer",
	[]() -> std::shared_ptr<MovingObject> { return std::make_shared<Player>(false,
		Keyboard(sf::Keyboard::Q, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, sf::Keyboard::S));  });

//-----------------------------------------------------------------------------
//draw plater
void Player::draw(sf::RenderWindow& window) const {

	if (m_aura)
	{
		if (!m_playerSide)
			m_power->drawAura(window,m_sprite.getPosition(),m_sprite.getOrigin());
		else {
			auto position = sf::Vector2f(m_sprite.getPosition().x + 10, m_sprite.getPosition().y);
			m_power->drawAura(window, position, m_sprite.getOrigin());
		}
	}
  
	ScoreBoard::getInstance().draw(window);

	window.draw(m_sprite);

}
//-----------------------------------------------------------------------------
//function that find where to move and  call to another function 
void Player::move(sf::Vector2f pressed) {

	BaseMovePlayerState* nextState = m_currentMoveState->handleMoveStatus();

	if (nextState) 
		m_currentMoveState = nextState;

	// Check if the power is active
	if (m_powerOnPlayer) {

		// Check if more than 5 seconds have passed since the power was activated
		if (m_powerClock2.getElapsedTime().asSeconds() > 3) {
			m_powerOnPlayer = false;
			m_sprite.setColor(m_playerColor);

		}
	}
	else {

		m_currentMoveState->movement(m_sprite, m_playerSide, m_body);
		
	}
	update();



	bool valid = false;
	if (sf::Keyboard::isKeyPressed(m_keys.SLIDE) && ScoreBoard::getInstance().istProgressP2Full() && m_playerSide) {//power
		valid = true;
	}

	if (sf::Keyboard::isKeyPressed(m_keys.SLIDE) && ScoreBoard::getInstance().istProgressP1Full() && !m_playerSide) {//power
		valid = true;
	}

	if (valid)
	{
		resetProgress();
		m_aura = true;
		m_sound.play();
		m_sound.setLoop(true);
	}
	
	if (!m_aura)
		m_sound.stop();

}

//-----------------------------------------------------------------------------
// Reset to default position if not jumping
void Player::resetToPosition(sf::Vector2f startPos, int numOfJump, int posX, int posY) {

	sf::IntRect characterRect(startPos.x + numOfJump, startPos.y, 80, 90); // Assuming each character is 32x32 pixels
	// Set the texture rectangle to the character's position and size on the sprite sheet
	m_sprite.setTextureRect(characterRect);
	m_sprite.setPosition(float(m_basePosition.x + m_posX), float(m_basePosition.y + posY));
}
//-----------------------------------------------------------------------------
void Player::resetProgress()
{
	if (!m_playerSide)
	{
		ScoreBoard::getInstance().resetProgressP1();
	}
	else
	{
		ScoreBoard::getInstance().resetProgressP2();
	}

}
//-----------------------------------------------------------------------------
sf::Sprite& Player::getSprite() {
	return m_sprite;
}
//-----------------------------------------------------------------------------
void Player::reset() {
	// Update the position of the Box2D body
	b2Vec2 newPosition(m_basePosition.x / SCALE, m_basePosition.y / SCALE);
	m_body->SetTransform(newPosition, m_body->GetAngle());

	// Reset the velocity of the Box2D body
	m_body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));  // Set linear velocity to zero
	m_body->SetAngularVelocity(0.0f);               // Set angular velocity to zero
}

//-----------------------------------------------------------------------------
//get keys
Keyboard Player::getKey() const
{
	return m_keys;
}
//-----------------------------------------------------------------------------
std::shared_ptr<Power> Player::getPower()
{
	return m_power;
}

void Player::setAura(bool aura) {
	m_aura = aura;
}
//-----------------------------------------------------------------------------
bool Player::getAura() const{
	return m_aura;
}
//-----------------------------------------------------------------------------

void Player::update() {
	b2Vec2 position1 = m_body->GetPosition();
	m_sprite.setPosition(B2VecToSFVec(position1));
}

bool Player::getSideOfPlayer() {
	return m_playerSide;
}

bool Player::getSide() const {
	return m_playerSide;
}

b2Body* Player::getBody() {
	return m_body;
}

void Player::setPowerOnPlayer(bool powerOnPlayer) {
	m_powerOnPlayer = powerOnPlayer;
}

bool Player::getPowerOnPlayer() const {
	return m_powerOnPlayer;
}

void Player::restartClock() {
	m_powerClock2.restart().asSeconds();

}