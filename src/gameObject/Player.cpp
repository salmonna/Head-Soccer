
#pragma once
#include "gameObject/Player.h"
#include <iostream>
#include "Resources.h"
#include "power/FirePower.h"

//-----------------------------------------------------------------------------
Player::Player(bool right, Keyboard keys) :m_numOfJump(0), m_posX(0), m_posY(0), m_move(-2), m_gravity(0),m_keys(keys), m_playerSide(right)
, m_aura(false), m_standMoveState(&m_leftMoveState, &m_rightMoveState,&m_jumpMoveState,&m_kickMoveState), m_leftMoveState(&m_standMoveState, &m_jumpMoveState)
,m_jumpMoveState(&m_standMoveState,&m_kickMoveState), m_kickMoveState(&m_standMoveState,&m_jumpMoveState), m_rightMoveState(&m_standMoveState, &m_jumpMoveState),
m_currentMoveState(&m_standMoveState)
{

	sf::Vector2f pos;
	(m_playerSide) ? pos = sf::Vector2f(950, 80) : pos = sf::Vector2f(550, 80);
	m_power = std::make_unique<FirePower>(pos);
	
	if (m_playerSide)
	{
		m_sprite.setScale(-1, 1);
		m_basePosition = sf::Vector2f(1520, 770);
	}
	else
	{
		m_basePosition = sf::Vector2f(272, 770);
	}
	//----------------------box2d---------------------------//
	auto world = Box2d::getInstance().getBox2dWorld();
	// Create the player
	b2BodyDef playerBodyDef;
	playerBodyDef.type = b2_dynamicBody;
	playerBodyDef.bullet = true;
	playerBodyDef.position.Set(m_basePosition.x / SCALE, m_basePosition.y / SCALE);
	m_body = world->CreateBody(&playerBodyDef);
	b2PolygonShape playerBox;
	playerBox.SetAsBox(30.f / SCALE, 40.f / SCALE);
	b2FixtureDef playerFixtureDef;
	playerFixtureDef.shape = &playerBox;
	playerFixtureDef.density = 10.f;
	playerFixtureDef.friction = 0.4f;
	m_body->CreateFixture(&playerFixtureDef);

	// Set the gravity scale for the player
	m_body->SetGravityScale(PLAYER_GRAVITY_SCALE);

	m_sprite.setOrigin(30.f, 40.f);
	m_sprite.setTexture(Resources::getInstance().getCharactersTexture()[0]);
	resetToPosition();


	m_sprite.setPosition(m_basePosition);

}

//-----------------------------------------------------------------------------
void Player::activatePower(sf::Sprite& ball, sf::Sprite& player)
{
	m_power->activatePower(ball, player);
}
//-----------------------------------------------------------------------------
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
			m_power->drawAura(window,m_sprite.getPosition());
		else {
			auto position = sf::Vector2f(m_sprite.getPosition().x - 70, m_sprite.getPosition().y);
			m_power->drawAura(window, position);
		}
	}
  
	m_power->drawProcess(window);

	window.draw(m_sprite);

}
//-----------------------------------------------------------------------------
//function that find where to move and  call to another function 
void Player::move(sf::Vector2f pressed) {

	BaseMovePlayerState* nextState = m_currentMoveState->handleMoveStatus();

	if (nextState) {

		m_currentMoveState = nextState;
	}
	auto pos = sf::Vector2i(m_posX, m_posY);
	m_currentMoveState->movement(m_sprite,m_playerSide, m_body);

	update();

	m_posX = pos.x;
	m_posY = pos.y;

	if (sf::Keyboard::isKeyPressed(m_keys.SLIDE) && m_power->isProcessFull()) {//slide
		//playerObject.activatePower(ballObject.getSprite(), playerObject.getSprite());
		resetProgress();
		m_aura = true;
	}

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
	m_power->resetProgress();

}
//-----------------------------------------------------------------------------
sf::Sprite& Player::getSprite() {
	return m_sprite;
}
//-----------------------------------------------------------------------------
void Player::reset() {
	//m_sprite.setPosition(m_basePosition);
	// Update the position of the Box2D body
	b2Vec2 newPosition(m_basePosition.x / SCALE, m_basePosition.y / SCALE);
	//m_ball.setPosition(position);
	m_body->SetTransform(newPosition, m_body->GetAngle());
	//update();
}
//-----------------------------------------------------------------------------
sf::Vector2f Player::getPosition() const {

	return m_sprite.getPosition();
}
//-----------------------------------------------------------------------------
//get keys
Keyboard Player::getKey() const
{
	return m_keys;
}
//-----------------------------------------------------------------------------
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