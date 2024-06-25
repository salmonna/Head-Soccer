#pragma once
#include "Command.h"
#include "gameState/GameState.h"



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


SwichScreen::SwichScreen(GameState* gameState, Controller* controller) :m_gameStatePtr(gameState),
m_controllerPtr(controller)
{


}

void SwichScreen::execute()
{
	m_controllerPtr->setState(m_gameStatePtr);
}

SwichScreen::~SwichScreen()
{
}

