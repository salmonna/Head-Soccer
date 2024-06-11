
#pragma once
#include "gameObject/Player.h"
#include <iostream>
#include "Resources.h"

Player::Player(bool right, Keyboard keys) :m_numOfJump(0), m_posX(0), m_posY(0), m_move(-2), m_gravity(0),
										 m_keys(keys), m_playerSide(right)
{
	m_sprite.setTexture(Resources::getInstance().getCharactersTexture()[0]);
	resetToPosition();
	
	if (m_playerSide)
	{
		m_sprite.scale(-1, 1);
		m_sprite.setPosition(1200, 750);
	}
	else
	{
		m_sprite.setPosition(272, 750);
	}
	
	m_startSprite.push_back(sf::Vector2f(160, 126));
	m_startSprite.push_back(sf::Vector2f(160, 244));
	m_startSprite.push_back(sf::Vector2f(160, 8));
	m_startSprite.push_back(sf::Vector2f(160, 365));
}



//draw plater
void Player::draw(sf::RenderWindow& window) const {

	window.draw(m_sprite);
}

//function that find where to move and  call to another function 
void Player::move(sf::Vector2f pressed) {

	if (sf::Keyboard::isKeyPressed(m_keys.JUMP) || m_sprite.getPosition().y < 750) {//jump
		if (m_posY > -200)
			m_posY -= 15;
		
		movePlayer(m_startSprite[2], 7, 50);
	}
	else {
		// Reset to default position if not jumping
		resetToPosition();
	}

	if (sf::Keyboard::isKeyPressed(m_keys.SPACE))//kick
		movePlayer(m_startSprite[0], 7, 10);
	else if (sf::Keyboard::isKeyPressed(m_keys.LEFT)) {//move left
		m_posX -= 5;
		movePlayer(m_startSprite[1], 6, 10);
	}
	else if (sf::Keyboard::isKeyPressed(m_keys.RIGHT)) {//move right
		m_posX += 5;
		movePlayer(m_startSprite[1], 6, 10);
	}
	else if (sf::Keyboard::isKeyPressed(m_keys.SLIDE)) {//slide
	    (m_playerSide) ? m_posX -= 5 : m_posX += 5;
		movePlayer(m_startSprite[3], 6, 1);
	}

	// Handle gravity and ground collision
	updateGravityAndCollision();
}

//function that move the player
void Player::movePlayer(sf::Vector2f startPos, int maxSprite, float maxTime) {

	float sec = float(m_moveClock.getElapsedTime().asMilliseconds());
	if (maxTime < sec)
	{
		if (m_numOfJump > 110* maxSprite)
		{
			m_numOfJump = 0;
			m_move = -2;
			
			return;
		}
		else
		{
			m_moveClock.restart();
			m_numOfJump += 115;
			resetToPosition(startPos, m_numOfJump, m_posX, m_posY);
		}
		
	}
}


// Reset to default position if not jumping
void Player::resetToPosition(sf::Vector2f startPos,int numOfJump ,int posX, int posY) {

	sf::IntRect characterRect(startPos.x+ numOfJump, startPos.y, 80, 90); // Assuming each character is 32x32 pixels
	// Set the texture rectangle to the character's position and size on the sprite sheet
	m_sprite.setTextureRect(characterRect);
	m_sprite.setPosition(float(272 + m_posX), float(750+ posY));
}

// Handle gravity and ground collision
void Player::updateGravityAndCollision() {
	if (m_sprite.getPosition().y < 750)
	{
		m_sprite.setPosition(float(272 + m_posX), float(750 + m_posY + m_gravity));
		m_gravity += 5;
	}
	else
	{
		m_gravity = 0;
		m_posY = 0;
	}
}


sf::Sprite& Player::getSprite() {
	return m_sprite;
}

sf::Vector2f Player::getPosition() const {

	return m_sprite.getPosition();
}

//get keys
Keyboard Player::getKey() const 
{
	return m_keys;
}