#include "Command/SwichScreen.h"



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
