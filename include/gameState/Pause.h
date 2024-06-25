#pragma once
#include "GameState.h"
#include "Menu.h"
#include "Command/Button.h"


class Board;

class Pause : public GameState
{
public:
	Pause (Controller* controller, Menu* menuState, Board* boardState);

	virtual void draw(sf::RenderWindow & window) const override;
	virtual void respond(sf::Vector2f mousePressed) override;
	~Pause () = default;

private:
	std::vector<std::unique_ptr<Button>> m_buttons;

	Board* m_boardState;

};



