
#include "Player.h"

Player::Player(sf::Texture& texture):m_jump(0), m_pos(0),m_move(0)
{
	m_sprite.setTexture(texture);

	// Define the rectangle to select the character from the sprite sheet
	sf::IntRect characterRect(145, 125, 95, 100); // Assuming each character is 32x32 pixels

	// Set the texture rectangle to the character's position and size on the sprite sheet
	m_sprite.setTextureRect(characterRect);
	m_sprite.setPosition(272, 700);
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
		kick();
		m_movePlayer = true;

	case 71:
		moveLeft();
		m_movePlayer = true;

	}
	if (!m_movePlayer)
	{
		return;
	}

}

void Player::kick() {
	float sec = m_moveClock.getElapsedTime().asMilliseconds();
	if (100 > sec)
	{
		if (m_jump > 600)
		{
			m_jump = 0;
			m_pos = 0;

		}
		else
		{
			m_jump += 115;
			m_pos += 10;
		}
		sf::IntRect characterRect(160 + m_jump, 125, 95, 100); // Assuming each character is 32x32 pixels

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
		sf::IntRect characterRect(160 + m_jump, 125, 95, 100); // Assuming each character is 32x32 pixels

		// Set the texture rectangle to the character's position and size on the sprite sheet
		m_sprite.setTextureRect(characterRect);
		m_sprite.setPosition(272, 700);
		m_moveClock.restart();
	}
}


void Player::moveLeft() {
	float sec = m_moveClock.getElapsedTime().asMilliseconds();
	if (100 > sec)
	{
		if (m_jump > 600)
		{
			m_jump = 0;
			m_pos = 0;

		}
		else
		{
			m_jump += 115;
			m_pos += 10;
		}
		sf::IntRect characterRect(160 + m_jump, 125, 95, 100); // Assuming each character is 32x32 pixels

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
		sf::IntRect characterRect(160 + m_jump, 125, 95, 100); // Assuming each character is 32x32 pixels

		// Set the texture rectangle to the character's position and size on the sprite sheet
		m_sprite.setTextureRect(characterRect);
		m_sprite.setPosition(272, 700);
		m_moveClock.restart();
	}
}


Player::~Player()
{
}