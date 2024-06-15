#include "gameState/GameResults.h"
#include "Resources.h"
#include "button/ReplayButton.h"

//gameResults constactor
GameResults::GameResults(Menu* menuState): m_gameState(NULL)
{
	std::vector<sf::Texture>& texturs = Resources::getInstance().gameResultsTexture();
	m_sprite.setTexture(texturs[0]);
	//put all the button into one vector
	m_buttons.push_back(std::make_unique<ReplayButton>(texturs[1], menuState));
}

//respond function check if there is a click on the exit button
void GameResults::respond(sf::Vector2f mousePressed)
{
	//respond to the buttons pressed
	for (int i = 0; i < m_buttons.size(); i++)
	{
		if (m_buttons[i]->contains(mousePressed)) {

			m_gameState = m_buttons[i]->click();
			break;
		}
	}
}

//draw function
void GameResults::draw(sf::RenderWindow& window) const
{

	window.draw(m_sprite);
	//respond to the buttons pressed
	for (int i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i]->draw(window);
	}
}

GameState* GameResults::handleEvents() {
	GameState* gameState = m_gameState;
	m_gameState = NULL;
	return gameState;
}

