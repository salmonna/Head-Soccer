#pragma once
#include "Controller.h"
#include "Resources.h"

//controller constractor
Controller::Controller():m_menu(Resources::getInstance().getMenuTexture()),
m_gameBoard(Resources::getInstance().getBoardTexture()),m_gameResults(Resources::getInstance().gameResultsTexture())
{
	runTheGame();
}

//run the game function that mange the ehole game in loop
void Controller::runTheGame()
{

	m_window.open();

	while (m_window.isOpen())
	{
		m_window.eventFunc();
		m_window.display();
		m_window.clear();

		if (m_menu.isOpen())
		{
			m_menu.respond(m_window.getMousePressed());
			m_menu.draw(m_window.getWindow());
			if (m_menu.isExit())
			{
				m_window.close();
			}
			continue;
		}
		else if (m_gameBoard.isOpen())
		{
			m_gameBoard.respond(m_window.getMousePressed());
			m_gameBoard.draw(m_window.getWindow());
			continue;
		}
		else if (m_gameResults.isOpen() && false)
		{
			m_gameResults.respond(m_window.getMousePressed());
			m_gameResults.draw(m_window.getWindow());
			continue;
		}
		m_window.close();
	}
	
}

