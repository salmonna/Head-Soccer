
#pragma once
#include "Player.h"
#include <iostream>

Player::Player(sf::Texture& texture):m_jump(0), m_posX(0), m_posY(0), m_move(0), m_movePlayer(false)
{
	m_sprite.setTexture(texture);

	// Define the rectangle to select the character from the sprite sheet
	sf::IntRect characterRect(145, 125, 95, 100); // Assuming each character is 32x32 pixels

	// Set the texture rectangle to the character's position and size on the sprite sheet
	m_sprite.setTextureRect(characterRect);
	m_sprite.setPosition(272, 750);

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

//move the player 
void Player::move(int keyPressed) {

	//if user preesed keyboard keep it in member
	if (keyPressed != 0)
	{
		m_move = keyPressed;
		m_moveClock.restart();
	}

	switch (m_move)
	{
	case SPACE://kick
		movePlayer(m_startSprite[0],600);
		break;

	case LEFT://move left
		m_posX -= 5;
		movePlayer(m_startSprite[1], 720);
		break;

	case RIGHT://move right
		m_posX += 5;
		movePlayer(m_startSprite[1], 720);
		break;

	case JUMP://jump
		if (m_posY > -105)
		{
			m_posY -= 20;
		}
		movePlayer(m_startSprite[2], 400);

		//after jumping need to go down
		if (!m_movePlayer)
		{
			m_move = DOWN;
		}
		break;

	case DOWN://down
		m_posY += 20;
		movePlayer(m_startSprite[3], 400);
		break;

	case SLIDE://slide
		m_posX += 5;
		movePlayer(m_startSprite[4], 720);
		break;

	default://return to regular position 
		m_posY = 0;
		sf::IntRect characterRect(145, 585, 95, 100); // Assuming each character is 32x32 pixels
		// Set the texture rectangle to the character's position and size on the sprite sheet
		m_sprite.setTextureRect(characterRect);
		m_sprite.setPosition(float(272 + m_posX), float(750));
	}

}

void Player::movePlayer(sf::Vector2f startPos, int jump) {
	float sec = float(m_moveClock.getElapsedTime().asMilliseconds());
	if (200 > sec)
	{
		if (m_jump > jump)
		{
			m_jump = 0;
			m_move = 0;
			m_movePlayer = false;
			return;
		}
		else
		{
			m_jump += 115;
		}
		sf::IntRect characterRect(int(startPos.x + m_jump), int(startPos.y), 95, 100); // Assuming each character is 32x32 pixels

		// Set the texture rectangle to the character's position and size on the sprite sheet
		m_sprite.setTextureRect(characterRect);
		m_sprite.setPosition(float(272 + m_posX), float(750 + m_posY));
		m_movePlayer = true;
	}
	else
	{
		m_jump = 0;
		m_move = 0;
		m_movePlayer = false;
		sf::IntRect characterRect(int(startPos.x), int(startPos.y), 95, 100); // Assuming each character is 32x32 pixels

		// Set the texture rectangle to the character's position and size on the sprite sheet
		m_sprite.setTextureRect(characterRect);
		m_sprite.setPosition(float(272 + m_posX), float(750 + m_posY));
		m_moveClock.restart();
	}
}
