#pragma once 
#include "GameState.h"
#include "gameState/Board.h"
#include "button/BaseButton.h"
#include "button/StartButton.h"

class SelectTeam : public GameState
{
public:
	SelectTeam(Board* boardState);
	virtual ~SelectTeam();

	virtual void draw(sf::RenderWindow& window) const override;
	virtual void respond(sf::Vector2f mousePressed) override;
	virtual GameState* handleEvents() override;

private:

	GameState* m_gameState;
	sf::Sprite m_stage;
	std::vector<std::unique_ptr<BaseButton>> m_buttons;
	std::vector<sf::Sprite> m_charcters;
};

