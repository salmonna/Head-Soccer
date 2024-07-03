
#pragma once
#include "gameObject/UserPlayer.h"
#include <iostream>
#include "Resources.h"
#include "gameObject/scoreBoard.h"
#include "SoundControl.h"

//-----------------------------------------------------------------------------
// Constructor initializes UserPlayer object based on side and keyboard input
UserPlayer::UserPlayer(bool right, Keyboard keys) :m_keys(keys), m_PlayerSide(right), m_aura(false), m_powerOnPlayer(false),m_powerClock(),
m_currentMoveState(std::make_unique<StandPlayerState>())
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
	m_auraSound.setVolume(3);

}
//---------------------------------------- Factory ----------------------------------
// Registration of UserPlayer as a moving object for the MovingFactory
bool UserPlayer::m_registeritRightPlayer = MovingFactory::registeritMoving("RightPlayer",
	[]() -> std::shared_ptr<MovingObject> { return std::make_shared<UserPlayer>(true,
		Keyboard(sf::Keyboard::Space, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Down)); });

bool UserPlayer::m_registeritLeftPlayer = MovingFactory::registeritMoving("LeftPlayer",
	[]() -> std::shared_ptr<MovingObject> { return std::make_shared<UserPlayer>(false,
		Keyboard(sf::Keyboard::Q, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, sf::Keyboard::S));});

//-----------------------------------------------------------------------------
// Function that determines movement and updates player state 
void UserPlayer::move() {

	std::unique_ptr<BaseMovePlayerState> nextState = m_currentMoveState->handleMoveStatus();
	if (nextState) 
		m_currentMoveState = std::move(nextState);

	// Check if the power is active
	if (m_powerOnPlayer){
		if (m_powerClock.getElapsedTime().asSeconds() > 3)
			deactivatePower(m_body, m_sprite, m_PlayerColor, m_powerOnPlayer);
	}
	else if(!m_power->powerIsActive() && m_power->stayInTheAir()) {
		m_currentMoveState->movement(m_sprite, m_keys, m_body);
	}

	update();

	if (sf::Keyboard::isKeyPressed(m_keys.SLIDE))
		resetPlayerProgress();
}
//-----------------------------------------------------------------------------
// Reset player progress based on score board progress
void UserPlayer::resetPlayerProgress()
{
	if (ScoreBoard::getInstance().isProgressP1Full() && !m_PlayerSide)
	{
		ScoreBoard::getInstance().resetProgressP1();
		setAura(true);
	}
	else if(ScoreBoard::getInstance().isProgressP2Full() && m_PlayerSide)
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
// Update player position based on Box2D body position
void UserPlayer::update() {
	b2Vec2 position = m_body->GetPosition();
	m_sprite.setPosition(B2VecToSFVec(position));
}
//-----------------------------------------------------------------------------
// Draw player and associated elements on the window
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
// Get player's power object
std::shared_ptr<Power> UserPlayer::getPower()const
{
	return m_power;
}
//-----------------------------------------------------------------------------
// Get player sprite
sf::Sprite& UserPlayer::getSprite() {
	return m_sprite;
}
//-----------------------------------------------------------------------------
// Check if player has aura
bool UserPlayer::getAura() const{
	return m_aura;
}
//-----------------------------------------------------------------------------
// Set aura state for player
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
// Get player's side (true for right, false for left)
bool UserPlayer::getSideOfPlayer() const {
	return m_PlayerSide;
}
//-----------------------------------------------------------------------------
// Get Box2D body of player
b2Body* UserPlayer::getBody()const {
	return m_body;
}
//-----------------------------------------------------------------------------
// Get player's assigned keys
Keyboard UserPlayer::getKey() const
{
	return m_keys;
}
//-----------------------------------------------------------------------------
// Set power state for player
void UserPlayer::setPowerOnPlayer(bool powerOnPlayer) {
	m_powerOnPlayer = powerOnPlayer;
}
//-----------------------------------------------------------------------------
// Get power state for player
bool UserPlayer::getPowerOnPlayer() const {
	return m_powerOnPlayer;
}
//-----------------------------------------------------------------------------
// Restart power clock for player
void UserPlayer::restartClock() {
	m_powerClock.restart();
}
//-----------------------------------------------------------------------------
// Destructor cleans up Box2D body and associated fixtures
UserPlayer::~UserPlayer() {
	m_body->DestroyFixture(m_body->GetFixtureList());
	auto world = Box2d::getInstance().getBox2dWorld();
	world->DestroyBody(m_body);
	m_body = nullptr;
}