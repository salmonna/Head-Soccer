#pragma once
#include "Window.h"
#include <vector>
#include <memory>
#include "gameState/GameModeSelection.h"
#include "gameState/Tutorial.h"
#include "Command/Button.h"
#include "GameState.h"
#include <SFML/Audio.hpp>

//class Button;
class Controller;

class Menu: public GameState
{
public:
	Menu(Controller * controller, Tutorial * tutorial, GameModeSelection * gameModeState, sf::RenderWindow * window);

	virtual void draw(sf::RenderWindow & window) const override;
	virtual void respond(sf::Vector2f position) override;

private:

	sf::Sprite m_Stage;
	std::vector<std::unique_ptr<Button>> m_buttons;
	bool m_isSongPlayed;

};

