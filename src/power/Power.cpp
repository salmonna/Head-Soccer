#include "power/Power.h"
#include "Resources.h"


Power::Power(sf::Vector2f pos):m_progress(0), m_clock()
{
	std::vector<sf::Texture> & texture = Resources::getInstance().getPowerTexture();

	for (int i = 0; i < texture.size(); i++)
	{
		m_progressSprite.push_back(sf::Sprite());
		m_progressSprite[i].setTexture(texture[i]);
		m_progressSprite[i].scale(0.6, 1);
		m_progressSprite[i].setPosition(pos);
	}

}


void Power::drawProcess(sf::RenderWindow& window) 
{
	int width = (m_progress + 1) * 5;

	if (m_clock.getElapsedTime().asSeconds() >= 0.1 && width < 481)
	{
		m_progress++;
		m_clock.restart();
	}




	sf::IntRect characterRect(0, 0, width, m_progressSprite[1].getGlobalBounds().height);
	m_progressSprite[1].setTextureRect(characterRect);

	window.draw(m_progressSprite[0]);
	window.draw(m_progressSprite[1]);

}