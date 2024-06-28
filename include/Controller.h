#pragma once
#include "Window.h"
#include "gameState/Menu.h"
#include "Resources.h"
#include "gameState/Board.h"
#include "gameState/GameResults.h"
#include "gameState/GameState.h"
#include "gameState/GameModeSelection.h"
#include "gameState/SelectTeam.h"
#include "gameState/Pause.h"
#include "gameState/Tutorial.h"

class Controller
{
public:
	Controller();
    void setState(GameState* gameState);
    void undoState();

private:
	void runTheGame();

    Window m_window;
    GameResults m_gameResults;
    Board m_gameBoard;
    GameModeSelection m_gameMode;
    Tutorial m_tutorial;
    Menu m_menu;
    Pause m_pause;
    SelectTeam m_selectTeam;
	GameState * m_currentState;
};

