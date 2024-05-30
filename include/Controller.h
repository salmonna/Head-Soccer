#pragma once
#include "Window.h"
#include "Menu.h"
#include "Resources.h"
#include "Board.h"
#include "GameResults.h"

class Controller
{
public:
	Controller();

private:

	void runTheGame();

	Window m_window;
	Menu m_menu;
	Board m_gameBoard;
	GameResults m_gameResults;

};

