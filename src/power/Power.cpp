
#include "power/Power.h"
#include "Resources.h"
#include <iostream>
//------------------------------------------------------------------
Power::Power(): m_clock(), m_powerTimer(), m_powerIsActive(false)
{
	std::vector<sf::Texture>& texture = Resources::getInstance().getPowerTexture();
	m_auraSprite.setTexture(texture[2]);
	sf::IntRect characterRect(10, 0, 110, 150); // Assuming each character is 32x32 pixels
	// Set the texture rectangle to the character's position and size on the sprite sheet
	m_auraSprite.setTextureRect(characterRect);
}
//------------------------------------------------------------------
// Returns a reference to the aura sprite
sf::Sprite& Power::getSprite() {

	return m_auraSprite;
}
//------------------------------------------------------------------
// Starts the power and stay timers
void Power::startTimer()
{
	m_powerTimer.restart();
	m_stayTimer.restart();
}
//------------------------------------------------------------------
// Checks if the power timer has exceeded the duration
// If so, deactivates the power
void Power::checkTimeIsOver()
{
	if (m_powerTimer.getElapsedTime().asSeconds() >= 2.8f)
		m_powerIsActive = false;
}
//------------------------------------------------------------------
// Returns true if the stay timer has exceeded the air time duration
bool Power::stayInTheAir()
{
	return m_stayTimer.getElapsedTime().asSeconds() >= 2.f;
}
//------------------------------------------------------------------
// Draws the aura sprite at the specified position with the given origin
// Updates the texture rectangle based on elapsed time for animation
void Power::drawAura(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f origin) {
	m_auraSprite.setPosition(position.x - 25,position.y - 55);
	m_auraSprite.setOrigin(origin);
	window.draw(m_auraSprite);
	int timeSec = m_clock.getElapsedTime().asSeconds() * 10;

	sf::IntRect characterRect(10 + 140*(timeSec%3), 0, 110, 150); // Assuming each character is 32x32 pixels
	// Set the texture rectangle to the character's position and size on the sprite sheet
	m_auraSprite.setTextureRect(characterRect);
}
//------------------------------------------------------------------
// Sets the power active state
void Power::setPowerIsActive(bool powerIsActive)
{
	m_powerIsActive = powerIsActive;
}
//------------------------------------------------------------------
// Returns the current active state of the power
bool Power::powerIsActive()
{
	return m_powerIsActive;
}
