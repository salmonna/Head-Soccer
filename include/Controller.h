#pragma once
#include "Window.h"
#include "Menu.h"
#include "Resources.h"
#include "Board.h"
#include "GameResults.h"
#include "GameState.h"

class Controller
{
public:
	Controller();

private:

	void runTheGame();

	Window m_window;	
	GameResults m_gameResults;
	Board m_gameBoard;
	Menu m_menu;

	GameState * m_currentState;
};

