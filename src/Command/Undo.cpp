#include "Command/Undo.h"



Undo::Undo(Controller* controller) :m_controllerPtr(controller)
{


}

void Undo::execute()
{
	m_controllerPtr->undoState();
}
