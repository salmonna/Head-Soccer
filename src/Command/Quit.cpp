#include "Command/Quit.h"

//-----------------------------------------------------------
//Constructor
Quit::Quit(sf::RenderWindow* windowPtr):m_windowPtr(windowPtr)
{
}
//-----------------------------------------------------------
// Execute the command associated with the button
void Quit::execute()
{
	m_windowPtr->close();
}