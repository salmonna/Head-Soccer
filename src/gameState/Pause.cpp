#pragma once
#include "GameState\Pause.h"

Pause::Pause()
{
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


GameState* Pause::handleEvents()
{
	return m_gameState;
}
