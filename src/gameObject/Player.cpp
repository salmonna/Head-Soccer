
#pragma once
#include "gameObject/Player.h"
#include <iostream>
#include "Resources.h"
#include "gameObject/scoreBoard.h"

//-----------------------------------------------------------------------------
Player::Player(bool right, Keyboard keys) :m_keys(keys), m_playerSide(right), m_aura(false), m_powerOnPlayer(false),m_powerClock(),
m_standMoveState(&m_leftMoveState, &m_rightMoveState,&m_jumpMoveState,&m_kickMoveState), m_leftMoveState(&m_standMoveState, &m_jumpMoveState)
,m_jumpMoveState(&m_standMoveState,&m_kickMoveState), m_kickMoveState(&m_standMoveState,&m_jumpMoveState), m_rightMoveState(&m_standMoveState, &m_jumpMoveState),
m_currentMoveState(&m_standMoveState)
{
	if (!m_playerSide)
		m_basePosition = sf::Vector2f(272, 775);
	else
	{
		m_sprite.setScale(-1, 1);
		m_basePosition = sf::Vector2f(1520, 775);
	}

	//----------------------box2d---------------------------//
	m_body = Box2d::getInstance().createPlayer(m_basePosition);
	
	m_sprite.setOrigin(40.f, 40.f);
	m_sprite.setTexture(Resources::getInstance().getCharactersTexture());
	m_power = Resources::getInstance().getPower(m_playerSide);
	resetToPosition();
	m_playerColor = m_sprite.getColor();
	m_sprite.setPosition(m_basePosition);
	
	m_sound.setBuffer(Resources::getInstance().getBufferVec()[0]);

}
//---------------------------------------- Factory ----------------------------------

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
	if (m_powerOnPlayer && (m_powerClock.getElapsedTime().asSeconds() > 2)) 
		deactivatePower();
	else {
		m_currentMoveState->movement(m_sprite, m_keys, m_body);
	}

	update();

	if (sf::Keyboard::isKeyPressed(m_keys.SLIDE))
		resetPlayerProgress();
}
//-----------------------------------------------------------------------------
// Reset to default position if not jumping
void Player::resetToPosition(sf::Vector2f startPos) {

	sf::IntRect characterRect(startPos.x, startPos.y, 80, 90); // Assuming each character is 32x32 pixels
	// Set the texture rectangle to the character's position and size on the sprite sheet
	m_sprite.setTextureRect(characterRect);
	m_sprite.setPosition(float(m_basePosition.x ), float(m_basePosition.y));
}
//-----------------------------------------------------------------------------
void Player::resetPlayerProgress()
{
	if (ScoreBoard::getInstance().istProgressP1Full() && !m_playerSide)
	{
		ScoreBoard::getInstance().resetProgressP1();
		setAura(true);
	}
	else if(ScoreBoard::getInstance().istProgressP2Full() && m_playerSide)
	{
		ScoreBoard::getInstance().resetProgressP2();
		setAura(true);
	}
}
//-----------------------------------------------------------------------------
void Player::deactivatePower() {
	// Deactivate the power
	m_powerOnPlayer = false;
	m_sprite.setColor(m_playerColor);

	// Check if the player's Y position is greater than 900.f
	if (m_sprite.getPosition().y > 900.f) {
		// Adjust position if necessary
		b2Vec2 currentPosition = m_body->GetPosition();
		currentPosition.y = 26.f; // Move the body to the desired Y position

		// Update the body's position and fix the power-related sensor issue
		m_body->SetTransform(currentPosition, m_body->GetAngle());
		m_body->GetFixtureList()->SetSensor(false);
	}
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
void Player::update() {
	b2Vec2 position = m_body->GetPosition();
	m_sprite.setPosition(B2VecToSFVec(position));
}

//-----------------------------------------------------------------------------
std::shared_ptr<Power> Player::getPower()const
{
	return m_power;
}
//-----------------------------------------------------------------------------
sf::Sprite& Player::getSprite() {
	return m_sprite;
}
//-----------------------------------------------------------------------------
bool Player::getAura() const{
	return m_aura;
}
//-----------------------------------------------------------------------------
void Player::setAura(bool aura) {
	if (!m_aura && aura) {
		m_sound.play();
		m_sound.setLoop(true);
	}
	else
		m_sound.stop();

	m_aura = aura;
}
//-----------------------------------------------------------------------------
bool Player::getSideOfPlayer() const {
	return m_playerSide;
}
//-----------------------------------------------------------------------------
b2Body* Player::getBody()const {
	return m_body;
}
//-----------------------------------------------------------------------------//
//get keys
Keyboard Player::getKey() const
{
	return m_keys;
}
//-----------------------------------------------------------------------------
void Player::setPowerOnPlayer(bool powerOnPlayer) {
	m_powerOnPlayer = powerOnPlayer;
}
//-----------------------------------------------------------------------------
bool Player::getPowerOnPlayer() const {
	return m_powerOnPlayer;
}
//-----------------------------------------------------------------------------
void Player::restartClock() {
	m_powerClock.restart().asSeconds();
}
//-----------------------------------------------------------------------------
Player::~Player() {
	std::cout << " P-D" << std::endl;
	m_body->DestroyFixture(m_body->GetFixtureList());
	auto world = Box2d::getInstance().getBox2dWorld();
	world->DestroyBody(m_body);
	m_body = nullptr;
}