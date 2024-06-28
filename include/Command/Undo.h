#pragma once
#include "Controller.h"
#include "Command.h"


class GameState;

class Undo : public Command
{
public:
	Undo(Controller * controllerPtr);

	virtual void execute() override;

	~Undo() = default;

private:

	Controller* m_controllerPtr;

};
