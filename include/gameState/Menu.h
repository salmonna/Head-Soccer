#pragma once
#include "Window.h"
#include "button/BaseButton.h"
#include <vector>
#include <memory>
#include "gameState/GameModeSelection.h"
#include "GameState.h"

class Menu: public GameState
{
public:
	Menu(GameModeSelection * gameModeState, sf::RenderWindow * window);

	virtual void draw(sf::RenderWindow & window) const override;
	virtual void respond(sf::Vector2f mousePressed) override;
	virtual GameState * handleEvents() override;

private:

	std::vector<std::unique_ptr<BaseButton>> m_buttons;
	std::vector<bool> m_buttonPressed;
	GameState * m_gameState;
	sf::Sprite m_Stage;
};

