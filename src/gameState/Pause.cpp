#pragma once
#include "GameState\Pause.h"
#include "Command/SwichScreen.h"
#include "Command/Command.h"
#include "Resources.h"


Pause::Pause(Controller* controller, Menu * menuState, Board * boardState):
m_boardState(boardState)
{

	std::vector<sf::Texture> & texture = Resources::getInstance().getPauseTexture();
	m_buttons.push_back(std::make_unique<Button>(std::move(std::make_unique<SwichScreen>(boardState, controller)), texture[1], sf::Vector2f(845.f, 350.f))); //Resume Button
	m_buttons.push_back(std::make_unique<Button>(std::move(std::make_unique<SwichScreen>(menuState, controller)), texture[2], sf::Vector2f(845.f, 500.f))); //exit to menu Button


	
}


//check if there is a click on one of the menu buttons
void Pause::respond(sf::Vector2f pressed) {
	//respond to the buttons pressed
	for (int i = 0; i < m_buttons.size(); i++)
	{
		if (m_buttons[i]->contains(pressed)) {

			if (i == 1) //exit to menu
			{
				m_boardState->reset();
			}

			m_buttons[i]->execute();
			return;
		}
	}
}

//draw
void Pause::draw(sf::RenderWindow& window) const {


	m_boardState->drawGameObjects(window);

	for (int i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i]->draw(window);
	}
}

