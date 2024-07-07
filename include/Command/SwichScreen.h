#pragma once
#include "Command.h"
#include "Controller.h"

class GameState;

class SwichScreen : public Command
{
public:
	SwichScreen(GameState * gameState, Controller * controller);
	
	virtual void execute() override;

	~SwichScreen();

private:

	GameState * m_gameStatePtr;
	Controller * m_controllerPtr;

};



