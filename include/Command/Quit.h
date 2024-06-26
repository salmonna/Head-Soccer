#pragma once
#include <SFML/Graphics.hpp>
#include "Command.h"


class GameState;

class Quit : public Command
{
public:
	Quit(sf::RenderWindow * windowPtr);

	virtual void execute() override;

	~Quit() = default;

private:

	sf::RenderWindow* m_windowPtr;

};



