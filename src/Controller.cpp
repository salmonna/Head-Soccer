#pragma once
#include "Controller.h"
#include "Resources.h"


//controller constractor
Controller::Controller(): m_menu(this, &m_tutorial, &m_gameMode, &m_window.getWindow()), m_currentState(&m_menu)
, m_gameMode(this, &m_gameBoard,&m_menu,&m_selectTeam),m_gameBoard(this, &m_menu, &m_pause, &m_gameResults),m_gameResults(this, &m_menu),m_selectTeam(this, &m_gameMode,&m_gameBoard)
, m_pause(this, &m_menu, &m_gameBoard), m_tutorial(this, &m_menu)
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

		m_currentState->draw(m_window.getWindow());
		m_currentState->respond(m_window.getMousePressed());
	}

}


void Controller::setState(GameState * newState)
{
	m_currentState = newState;
}

