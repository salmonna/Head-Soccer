#include "power/Power.h"
#include "Resources.h"


Power::Power(sf::Vector2f pos):m_progress(0), m_clock()
{
	std::vector<sf::Texture>& texture = Resources::getInstance().getPowerTexture();
	m_auraSprite.setTexture(texture[2]);
	sf::IntRect characterRect(35, 0, 120, 150); // Assuming each character is 32x32 pixels
	// Set the texture rectangle to the character's position and size on the sprite sheet
	m_auraSprite.setTextureRect(characterRect);


	for (int i = 0; i < texture.size(); i++)
	{
		m_progressSprite.push_back(sf::Sprite());
		m_progressSprite[i].setTexture(texture[i]);
		m_progressSprite[i].scale(0.6, 1);
		m_progressSprite[i].setPosition(pos);
	}

}





sf::Sprite& Power::getSprite() {

	return m_auraSprite;
}

void Power::drawProcess(sf::RenderWindow& window)
{
	int width = (m_progress + 1) * 8;

	if (m_clock.getElapsedTime().asSeconds() >= 0.1 && width < 490)
	{
		m_progress++;
		m_clock.restart();
	}

	sf::IntRect characterRect(0, 0, width, m_progressSprite[1].getGlobalBounds().height);
	m_progressSprite[1].setTextureRect(characterRect);

	window.draw(m_progressSprite[0]);
	window.draw(m_progressSprite[1]);

}


void Power::resetProgress()
{
	m_progress = 0;
}

void Power::drawAura(sf::RenderWindow& window, sf::Vector2f position) {
	m_auraSprite.setPosition(position.x - 5,position.y - 50);
	window.draw(m_auraSprite);
}