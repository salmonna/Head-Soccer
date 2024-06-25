#pragma once
#include "GameState.h"
#include "button/BaseButton.h"
#include "Menu.h"
#include "button/BaseButton.h"


class Board;

class Pause : public GameState , public BaseButton
{
public:
	Pause (Menu* menuState, Board* boardState);

	virtual void draw(sf::RenderWindow & window) const override;
	virtual void respond(sf::Vector2f mousePressed) override;
	virtual bool contains(sf::Vector2f position) const override;
	virtual GameState * click() override;
	~Pause () = default;

private:
	std::vector<std::unique_ptr<BaseButton>> m_buttons;
	GameState* m_gameState;
	Board* m_boardState;
	sf::Sprite m_sprite;
	bool m_pauseStateBool;

};



