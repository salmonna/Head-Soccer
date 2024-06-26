#include "gameState/GameResults.h"
#include "Resources.h"
#include "Command/SwichScreen.h"
#include "Command/Command.h"

//gameResults constactor
GameResults::GameResults(Controller* controller, Menu* menuState): m_gameState(NULL)
{
	std::vector<sf::Texture>& texture = Resources::getInstance().getGameModeTexture();
	m_sprite.setTexture(texture[0]);

	std::vector<sf::Texture>& texture2 = Resources::getInstance().getPauseTexture();
	m_buttons.push_back(std::make_unique<Button>(std::move(std::make_unique<SwichScreen>(menuState, controller)), texture2[2], sf::Vector2f(845.f, 500.f))); //exit to menu Button

	//put all the button into one vector
	//m_buttons.push_back(std::make_unique<ExitButton>(menuState));
}

//respond function check if there is a click on the exit button
void GameResults::respond(sf::Vector2f mousePressed)
{
	//respond to the buttons pressed
	for (int i = 0; i < m_buttons.size(); i++)
	{
		if (m_buttons[i]->contains(mousePressed)) {

			m_buttons[i]->execute();
			return;
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
