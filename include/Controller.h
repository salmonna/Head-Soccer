#pragma once
#include "Window.h"
#include "gameState/Menu.h"
#include "Resources.h"
#include "gameState/Board.h"
#include "gameState/GameResults.h"
#include "gameState/GameState.h"
#include "gameState/GameModeSelection.h"
#include "gameState/SelectTeam.h"

class Controller
{
public:
	Controller();

private:

	void runTheGame();
    void setState(GameState* newState);

    Window m_window;
    GameResults m_gameResults;
    Board m_gameBoard;
    GameModeSelection m_gameMode;
    Menu m_menu;
    SelectTeam m_selectTeam;

	GameState * m_currentState;
};

