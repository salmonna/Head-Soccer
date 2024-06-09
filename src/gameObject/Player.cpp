
#pragma once
#include "gameObject/Player.h"
#include <iostream>
#include "Resources.h"

Player::Player(bool right, Keyboard keys):m_numOfJump(0), m_posX(0), m_posY(0), m_move(-2),m_gravity(0),
							m_moveDown(false), m_movePlayer(false), m_keys(keys), m_playerSide(right)
{
	m_sprite.setTexture(Resources::getInstance().getCharactersTexture()[0]);

	// Define the rectangle to select the character from the sprite sheet
	sf::IntRect characterRect(145, 125, 95, 100); // Assuming each character is 32x32 pixels

	// Set the texture rectangle to the character's position and size on the sprite sheet
	m_sprite.setTextureRect(characterRect);
	m_sprite.setPosition(272, 750);
	if (m_playerSide)
	{
		m_sprite.scale(-1, 1);
	}

	m_startSprite.push_back(sf::Vector2f(145, 125));
	m_startSprite.push_back(sf::Vector2f(145, 240));
	m_startSprite.push_back(sf::Vector2f(145, 5));
	m_startSprite.push_back(sf::Vector2f(145, 455));
	m_startSprite.push_back(sf::Vector2f(145, 360));

}

//draw plater
void Player::draw(sf::RenderWindow& window) {

	window.draw(m_sprite);
}

//function that find where to move and  call to another function 
void Player::move(int keyPressed) {

	//if user preesed keyboard keep it in member
	if (keyPressedValid(keyPressed))
	{
		m_move = keyPressed;
		m_moveClock.restart();
	}

	if (m_move == m_keys.JUMP) {//jump
		/*if (m_posY > -105)
		{
			m_posY -= 20;
		}*/
		
		m_posY -= 20;
		movePlayer(m_startSprite[2], 3);

		//after jumping need to go down
		if (!m_movePlayer)
		{
			m_moveDown = true;
		}
	}
	else if (m_move == m_keys.SPACE)//kick
		movePlayer(m_startSprite[0], 7);
	else if (m_move == m_keys.LEFT) {//move left
		m_posX -= 5;
		movePlayer(m_startSprite[1], 6);
	}
	else if (m_move == m_keys.RIGHT) {//move right
		m_posX += 5;
		movePlayer(m_startSprite[1], 6);
	}
	else if (m_move == m_keys.SLIDE) {//slide
		if (m_playerSide)
			m_posX -= 5;
		else m_posX += 5;

		movePlayer(m_startSprite[4], 7);
	}
	else if (m_moveDown) {//down
		m_posY += 20;
		movePlayer(m_startSprite[3], 3);
		if (m_posY >= 0)
		{
			m_moveDown = false;
		}
	}
	else {//return to regular position 
		m_posY = 0;
		sf::IntRect characterRect(145, 585, 95, 100); // Assuming each character is 32x32 pixels
		// Set the texture rectangle to the character's position and size on the sprite sheet
		m_sprite.setTextureRect(characterRect);
		m_sprite.setPosition(float(272 + m_posX), float(750));
	}

}

//function that move the player
void Player::movePlayer(sf::Vector2f startPos, int maxSprite) {

	float maxTime = 200;
	float sec = float(m_moveClock.getElapsedTime().asMilliseconds());
	if (maxTime > sec)
	{
		if (m_numOfJump > 115* maxSprite)
		{
			m_numOfJump = 0;
			m_move = -2;
			m_gravity = 0;
			m_posY = 0;
			m_movePlayer = false;
			return;
		}
		else
		{
			m_numOfJump += 115;
		}
		m_movePlayer = true;
	}
	else
	{
		m_numOfJump = 0;
		m_move = -2;
		m_gravity = 0;
		m_posY = 0;
		m_movePlayer = false;
		m_moveClock.restart();
	}		
	sf::IntRect characterRect(int(startPos.x + m_numOfJump), int(startPos.y), 95, 100); // Assuming each character is 32x32 pixels
	
	// Set the texture rectangle to the character's position and size on the sprite sheet
	m_sprite.setTextureRect(characterRect);
	m_sprite.setPosition(float(272 + m_posX), float(750 + m_posY));
	//m_sprite.move(float(272 + m_posX), float(750 + m_posY));
}

//function that check if user pressed on valid key
bool Player::keyPressedValid(int keyPressed) {


	if (m_keys.SPACE == keyPressed)//kick
		return true;
	else if (m_keys.LEFT == keyPressed)//move left
		return true;
	else if (m_keys.RIGHT == keyPressed)//move right
		return true;
	else if (m_keys.JUMP == keyPressed)//jump
		return true;
	else if (m_keys.SLIDE == keyPressed)//slide
		return true;

	return false;
}

sf::Sprite& Player::getSprite() {
	return m_sprite;
}

int Player::getKeypressed() {
	return m_move;
}