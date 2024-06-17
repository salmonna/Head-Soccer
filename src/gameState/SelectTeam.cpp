#include "gameState/SelectTeam.h"


SelectTeam::SelectTeam(Board* boardState):m_gameState(NULL)
{
	m_stage.setTexture(Resources::getInstance().getGameModeTexture()[0]);
	m_buttons.push_back(std::make_unique<StartButton>(boardState));

	std::vector<sf::Texture>& charctersTexture = Resources::getInstance().getSelectTeam();
	
	auto sprite = sf::Sprite(charctersTexture[1]);
	sprite.setPosition(670, 50);
	m_charcters.push_back(sprite);

	for (size_t i = 2; i < charctersTexture.size(); i++)
	{
		sprite.setTexture(charctersTexture[i]);
		sprite.scale(0.6f,0.6f);
		m_charcters.push_back(sprite);
	}

}

void SelectTeam::draw(sf::RenderWindow& window) const {

	window.draw(m_stage);

	for (int i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i]->draw(window);
	}

	for (int i = 0; i < m_charcters.size(); i++)
	{
		window.draw(m_charcters[i]);
	}
}

void SelectTeam::respond(sf::Vector2f mousePressed) {
	//respond to the buttons pressed
	for (int i = 0; i < m_buttons.size(); i++)
	{
		if (m_buttons[i]->contains(mousePressed)) {

			m_gameState = m_buttons[i]->click();
			break;
		}
	}
}

GameState* SelectTeam::handleEvents() {

	GameState* gameState = m_gameState;
	m_gameState = NULL;
	return gameState;
}


SelectTeam::~SelectTeam()
{
}