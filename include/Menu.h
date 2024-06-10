#pragma once
#include "Window.h"
#include "button/BaseButton.h"
#include <vector>
#include <memory>
#include "Board.h"
#include "GameState.h"

class Menu: public GameState
{
public:
	Menu(Board * boardState, sf::RenderWindow * window);

	virtual void draw(sf::RenderWindow & window) const override;
	virtual void respond(sf::Vector2f mousePressed) override;
	virtual GameState * handleEvents() override;

	bool isOpen() const;

	bool isExit() const;

private:

	bool m_menuOpen;
	bool m_exit;
	bool m_play;

	std::vector<std::unique_ptr<BaseButton>> m_buttons;
	std::vector<bool> m_buttonPressed;
	GameState * m_gameState;
	sf::Sprite m_Stage;
};

