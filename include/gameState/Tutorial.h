#pragma once
#include "GameState.h"
#include "Command/Button.h"


class Menu;
class Controller;

class Tutorial : public GameState
{
public:
	Tutorial(Controller * controller, Menu* prevState);
	virtual void draw(sf::RenderWindow & window) const override;
	virtual void respond(sf::Vector2f mousePressed) override;
	~Tutorial() = default;

private:
	std::vector<std::unique_ptr<Button>> m_buttons;

	sf::Sprite m_sprite;

};