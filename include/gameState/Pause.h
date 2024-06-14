#pragma once
#include "GameState.h"
#include "button/BaseButton.h"
#include "Menu.h"


class Board;

class Pause : public GameState
{
public:
	Pause (Menu* menuState, Board* boardState);

	virtual void draw(sf::RenderWindow & window) const override;
	virtual void respond(sf::Vector2f mousePressed) override;
	virtual GameState* handleEvents() override;

	~Pause () = default;

private:
	std::vector<std::unique_ptr<BaseButton>> m_buttons;
	GameState* m_gameState;
	sf::Sprite m_Stage;


};



