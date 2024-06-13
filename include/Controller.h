#pragma once
#include "Window.h"
#include "gameState/Menu.h"
#include "Resources.h"
#include "gameState/Board.h"
#include "gameState/GameResults.h"
#include "gameState/GameState.h"
#include "gameState/GameModeSelection.h"

class Controller
{
public:
	Controller();

private:

	void runTheGame();

    Window m_window;
    GameResults m_gameResults;
    Board m_gameBoard;
    GameModeSelection m_gameMode;
    Menu m_menu;
    
	GameState * m_currentState;
};

