#include "gameState/GameResults.h"
#include "Resources.h"
#include "button/pauseButton/ExitButton.h"

//gameResults constactor
GameResults::GameResults(Menu* menuState): m_gameState(NULL)
{
	std::vector<sf::Texture>& texturs = Resources::getInstance().gameResultsTexture();

	for (int i = 0; i < texturs.size(); i++)
	{
		auto sprite = sf::Sprite(texturs[i]);
		m_resultSprite.push_back(sprite);
	}
	//put all the button into one vector
	m_buttons.push_back(std::make_unique<ExitButton>(menuState));
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

	for (int i = 0; i < m_resultSprite.size(); i++)
	{
		window.draw(m_resultSprite[i]);
	}
	
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
