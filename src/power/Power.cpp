
#include "power/Power.h"
#include "Resources.h"


Power::Power(): m_clock(), m_powerTimer(), m_stayTimer(), m_powerIsActive(false)
{
	std::vector<sf::Texture>& texture = Resources::getInstance().getPowerTexture();
	m_auraSprite.setTexture(texture[2]);
	sf::IntRect characterRect(10, 0, 110, 150); // Assuming each character is 32x32 pixels
	// Set the texture rectangle to the character's position and size on the sprite sheet
	m_auraSprite.setTextureRect(characterRect);
}


sf::Sprite& Power::getSprite() {

	return m_auraSprite;
}


void Power::startTimer()
{
	m_powerTimer.restart();
	m_stayTimer.restart();
}

bool Power::isTimeIsOver()
{
	if (m_powerTimer.getElapsedTime().asSeconds() >= 3.f)
	{
		m_powerIsActive = false;
		return true;
	}
	return false;
}

bool Power::stayInTheAir()
{
	return m_stayTimer.getElapsedTime().asSeconds() >= 2.f;
}


void Power::drawAura(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f origin) {
	m_auraSprite.setPosition(position.x - 25,position.y - 55);
	m_auraSprite.setOrigin(origin);
	window.draw(m_auraSprite);
	int timeSec = m_clock.getElapsedTime().asSeconds() * 10;

	sf::IntRect characterRect(10 + 140*(timeSec%3), 0, 110, 150); // Assuming each character is 32x32 pixels
	// Set the texture rectangle to the character's position and size on the sprite sheet
	m_auraSprite.setTextureRect(characterRect);
}

void Power::setPowerIsActive(bool powerIsActive)
{
	m_powerIsActive = powerIsActive;
}

bool Power::powerIsActive()
{
	return m_powerIsActive;
}
