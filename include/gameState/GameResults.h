#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "Command/Button.h"


//forward declartion
class Menu;
class Controller;

class GameResults: public GameState
{
public:
	GameResults(Controller * controller, Menu * menuState);

	virtual void draw(sf::RenderWindow& window) const override;
	virtual void respond(sf::Vector2f mousePressed) override;

	~GameResults() = default;

private:
	std::vector<std::unique_ptr<Button>> m_buttons;
	sf::Sprite m_sprite;
	GameState* m_gameState;
	
	std::vector<sf::Text> m_resultText;
};