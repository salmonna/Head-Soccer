#pragma once
#include "GameState\Pause.h"
#include "../../include/button/pauseButton/ResumeButton.h"
#include "../../include/button/pauseButton/ExitButton.h"




Pause::Pause(Menu * menuState, Board * boardState):m_gameState(NULL)
{
	m_buttons.push_back(std::make_unique<ResumeButton>(boardState));
	m_buttons.push_back(std::make_unique<ExitButton>(menuState));
}


//check if there is a click on one of the menu buttons
void Pause::respond(sf::Vector2f pressed) {
	//respond to the buttons pressed
	for (int i = 0; i < m_buttons.size(); i++)
	{
		if (m_buttons[i]->contains(pressed)) {

			m_gameState = m_buttons[i]->click();
			break;
		}
	}
}

//draw
void Pause::draw(sf::RenderWindow& window) const {

	//window.draw(m_Stage);

	for (int i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i]->draw(window);
	}
}


GameState * Pause::handleEvents()
{
	auto state = m_gameState;
	m_gameState = NULL;
	return state;
}
