#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "button/BaseButton.h"

//forwaard declartion
class Menu;

class GameResults: public GameState
{
public:
	GameResults(Menu * menuState);

	virtual void draw(sf::RenderWindow& window) const override;
	virtual void respond(sf::Vector2f mousePressed) override;
	virtual GameState * handleEvents() override;

	~GameResults() = default;

private:
	std::vector<std::unique_ptr<BaseButton>> m_buttons;
	std::vector<sf::Sprite> m_resultSprite;
	GameState* m_gameState;
};