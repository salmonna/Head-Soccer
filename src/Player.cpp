
#pragma once
#include "Player.h"

Player::Player(sf::Texture& texture):m_jump(0), m_pos(0),m_move(0)
{
	m_sprite.setTexture(texture);

	// Define the rectangle to select the character from the sprite sheet
	sf::IntRect characterRect(145, 125, 95, 100); // Assuming each character is 32x32 pixels

	// Set the texture rectangle to the character's position and size on the sprite sheet
	m_sprite.setTextureRect(characterRect);
	m_sprite.setPosition(272, 700);

	m_startSprite.push_back(sf::Vector2f(145, 125));
	m_startSprite.push_back(sf::Vector2f(145, 280));
}

void Player::draw(sf::RenderWindow& window) {

	window.draw(m_sprite);
}

void Player::move(int keyPressed) {
	
	if (keyPressed != 0)
	{
		m_move = keyPressed;
		m_moveClock.restart();
	}

	switch (m_move)
	{
	case 57:
		movePlayer(m_startSprite[0],600);
		m_movePlayer = true;

	case 71:
		movePlayer(m_startSprite[1], 600);
		m_movePlayer = true;

	}
	if (!m_movePlayer)
	{
		return;
	}

}

void Player::movePlayer(sf::Vector2f startPos, int jump) {
	float sec = m_moveClock.getElapsedTime().asMilliseconds();
	if (100 > sec)
	{
		if (m_jump > jump)
		{
			m_jump = 0;
			m_pos = 0;

		}
		else
		{
			m_jump += 115;
			m_pos += 10;
		}
		sf::IntRect characterRect(startPos.x + m_jump, startPos.y, 95, 100); // Assuming each character is 32x32 pixels

		// Set the texture rectangle to the character's position and size on the sprite sheet
		m_sprite.setTextureRect(characterRect);
		m_sprite.setPosition(272, 700);

	}
	else
	{
		m_jump = 0;
		m_pos = 0;
		m_move = 0;
		m_movePlayer = false;
		sf::IntRect characterRect(startPos.x + m_jump, startPos.y, 95, 100); // Assuming each character is 32x32 pixels

		// Set the texture rectangle to the character's position and size on the sprite sheet
		m_sprite.setTextureRect(characterRect);
		m_sprite.setPosition(272, 700);
		m_moveClock.restart();
	}
}

