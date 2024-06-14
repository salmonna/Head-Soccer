#pragma once
#include "Controller.h"
#include "Resources.h"


//controller constractor
Controller::Controller(): m_menu(&m_gameMode, &m_window.getWindow()), m_currentState(&m_menu)
,m_gameResults(), m_gameMode(&m_gameBoard), m_gameBoard(&m_menu)
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

		GameState * nextState = m_currentState->handleEvents();
		if (nextState)
		{
			m_currentState = nextState;
		}

		m_currentState->respond(m_window.getMousePressed());
		m_currentState->draw(m_window.getWindow());
	}

}



