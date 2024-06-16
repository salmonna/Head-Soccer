#pragma once
#include "GameState\Pause.h"
#include "../../include/button/pauseButton/ResumeButton.h"
#include "../../include/button/pauseButton/ExitButton.h"




Pause::Pause(Menu * menuState, Board * boardState):m_gameState(NULL), 
m_boardState(boardState), m_pauseStateBool(false)
{
	m_sprite.setTexture(Resources::getInstance().getPauseTexture()[0]);

	m_buttons.push_back(std::make_unique<ResumeButton>(boardState));
	m_buttons.push_back(std::make_unique<ExitButton>(menuState));
	
}


//check if there is a click on one of the menu buttons
void Pause::respond(sf::Vector2f pressed) {
	//respond to the buttons pressed
	for (int i = 0; i < m_buttons.size(); i++)
	{
		if (m_buttons[i]->contains(pressed)) {

			if (i == 1)
			{
				m_boardState->reset();
			}

			m_pauseStateBool = false;
			m_gameState = m_buttons[i]->click();
			return;
		}
	}
}

//draw
void Pause::draw(sf::RenderWindow& window) const {

	if (m_pauseStateBool)
	{
		m_boardState->drawGameObjects(window);

		for (int i = 0; i < m_buttons.size(); i++)
		{
			m_buttons[i]->draw(window);
		}
	}
	else
	{
		window.draw(m_sprite);
	}
}


GameState* Pause::click() 
{
	m_pauseStateBool = true;
	return this;
}


bool Pause::contains(sf::Vector2f position) const
{
	sf::Vector2f newPos = m_sprite.getTransform().getInverse().transformPoint(position);
	return m_sprite.getLocalBounds().contains(newPos);
}


GameState * Pause::handleEvents()
{
	auto state = m_gameState;
	m_gameState = NULL;
	return state;
}
