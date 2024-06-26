#include "Command/Quit.h"


Quit::Quit(sf::RenderWindow* windowPtr):m_windowPtr(windowPtr)
{

}

void Quit::execute()
{
	m_windowPtr->close();
}