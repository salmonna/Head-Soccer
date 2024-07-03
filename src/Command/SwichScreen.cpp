#include "Command/SwichScreen.h"


//-----------------------------------------------------------
//Constructor
SwichScreen::SwichScreen(GameState* gameState, Controller* controller) :m_gameStatePtr(gameState),
m_controllerPtr(controller)
{


}
//-----------------------------------------------------------
// Execute the command associated with the button
void SwichScreen::execute()
{
	m_controllerPtr->setState(m_gameStatePtr);
}
//-----------------------------------------------------------
//D-tor
SwichScreen::~SwichScreen()
{
}
