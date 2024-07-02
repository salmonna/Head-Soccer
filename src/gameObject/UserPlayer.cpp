
#pragma once
#include "gameObject/UserPlayer.h"
#include <iostream>
#include "Resources.h"
#include "gameObject/scoreBoard.h"
#include "SoundControl.h"

//-----------------------------------------------------------------------------
UserPlayer::UserPlayer(bool right, Keyboard keys) :m_keys(keys), m_PlayerSide(right), m_aura(false), m_powerOnPlayer(false),m_powerClock(),
m_standMoveState(&m_leftMoveState, &m_rightMoveState,&m_jumpMoveState,&m_kickMoveState), m_leftMoveState(&m_standMoveState, &m_jumpMoveState)
,m_jumpMoveState(&m_standMoveState,&m_kickMoveState), m_kickMoveState(&m_standMoveState,&m_jumpMoveState), m_rightMoveState(&m_standMoveState, &m_jumpMoveState),
m_currentMoveState(&m_standMoveState)
{
	if (!m_PlayerSide)
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
	m_power = Resources::getInstance().getPower(m_PlayerSide);
	resetToPosition(m_sprite, m_basePosition); 
	m_PlayerColor = m_sprite.getColor();
	m_sprite.setPosition(m_basePosition);

	m_auraSound.setBuffer(Resources::getInstance().getBufferVec()[0]);

}
//---------------------------------------- Factory ----------------------------------

bool UserPlayer::m_registeritRightPlayer = MovingFactory::registeritMoving("RightPlayer",
	[]() -> std::shared_ptr<MovingObject> { return std::make_shared<UserPlayer>(true,
		Keyboard(sf::Keyboard::Space, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Down)); });

bool UserPlayer::m_registeritLeftPlayer = MovingFactory::registeritMoving("LeftPlayer",
	[]() -> std::shared_ptr<MovingObject> { return std::make_shared<UserPlayer>(false,
		Keyboard(sf::Keyboard::Q, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, sf::Keyboard::S));  });

//-----------------------------------------------------------------------------
//function that find where to move and  call to another function 
void UserPlayer::move() {

	BaseMovePlayerState* nextState = m_currentMoveState->handleMoveStatus();
	if (nextState) 
		m_currentMoveState = nextState;

	// Check if the power is active
	if (m_powerOnPlayer && (m_powerClock.getElapsedTime().asSeconds() > 2)) 
		deactivatePower(m_body,m_sprite,m_PlayerColor,m_powerOnPlayer);
	else {
		m_currentMoveState->movement(m_sprite, m_keys, m_body);
	}

	update();

	if (sf::Keyboard::isKeyPressed(m_keys.SLIDE))
		resetPlayerProgress();
}
//-----------------------------------------------------------------------------
void UserPlayer::resetPlayerProgress()
{
	if (ScoreBoard::getInstance().istProgressP1Full() && !m_PlayerSide)
	{
		ScoreBoard::getInstance().resetProgressP1();
		setAura(true);
	}
	else if(ScoreBoard::getInstance().istProgressP2Full() && m_PlayerSide)
	{
		ScoreBoard::getInstance().resetProgressP2();
		setAura(true);
	}
}

//-----------------------------------------------------------------------------
void UserPlayer::reset() {
	// Update the position of the Box2D body
	b2Vec2 newPosition(m_basePosition.x / SCALE, m_basePosition.y / SCALE);
	m_body->SetTransform(newPosition, m_body->GetAngle());

	// Reset the velocity of the Box2D body
	m_body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));  // Set linear velocity to zero
	m_body->SetAngularVelocity(0.0f);               // Set angular velocity to zero
}
//-----------------------------------------------------------------------------
void UserPlayer::update() {
	b2Vec2 position = m_body->GetPosition();
	m_sprite.setPosition(B2VecToSFVec(position));
}
//-----------------------------------------------------------------------------
//draw plater
void UserPlayer::draw(sf::RenderWindow& window) const {

	if (m_aura)
	{
		if (!m_PlayerSide)
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
std::shared_ptr<Power> UserPlayer::getPower()const
{
	return m_power;
}
//-----------------------------------------------------------------------------
sf::Sprite& UserPlayer::getSprite() {
	return m_sprite;
}
//-----------------------------------------------------------------------------
bool UserPlayer::getAura() const{
	return m_aura;
}
//-----------------------------------------------------------------------------
void UserPlayer::setAura(bool aura) {
	if (!m_aura && aura) {
		m_auraSound.play();
		m_auraSound.setLoop(true);
	}
	else
		m_auraSound.stop();

	m_aura = aura;
}
//-----------------------------------------------------------------------------
bool UserPlayer::getSideOfPlayer() const {
	return m_PlayerSide;
}
//-----------------------------------------------------------------------------
b2Body* UserPlayer::getBody()const {
	return m_body;
}
//-----------------------------------------------------------------------------//
//get keys
Keyboard UserPlayer::getKey() const
{
	return m_keys;
}
//-----------------------------------------------------------------------------
void UserPlayer::setPowerOnPlayer(bool powerOnPlayer) {
	m_powerOnPlayer = powerOnPlayer;
}
//-----------------------------------------------------------------------------
bool UserPlayer::getPowerOnPlayer() const {
	return m_powerOnPlayer;
}
//-----------------------------------------------------------------------------
void UserPlayer::restartClock() {
	m_powerClock.restart().asSeconds();
}
//-----------------------------------------------------------------------------
UserPlayer::~UserPlayer() {
	std::cout << " P-D" << std::endl;
	m_body->DestroyFixture(m_body->GetFixtureList());
	auto world = Box2d::getInstance().getBox2dWorld();
	world->DestroyBody(m_body);
	m_body = nullptr;
}