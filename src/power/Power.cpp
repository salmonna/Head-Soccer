#include "power/Power.h"
#include "Resources.h"


Power::Power()
{
	std::vector<sf::Texture>& texturs = Resources::getInstance().getPowerTexture();
	m_auraSprite.setTexture(texturs[0]);
	sf::IntRect characterRect(35, 0, 120, 150); // Assuming each character is 32x32 pixels
	// Set the texture rectangle to the character's position and size on the sprite sheet
	m_auraSprite.setTextureRect(characterRect);
}

sf::Sprite& Power::getSprite() {

	return m_auraSprite;
}

void Power::drawProcess(sf::RenderWindow& window) const
{

}

void Power::drawAura(sf::RenderWindow& window, sf::Vector2f position) {
	m_auraSprite.setPosition(position.x - 5,position.y - 50);
	window.draw(m_auraSprite);
}