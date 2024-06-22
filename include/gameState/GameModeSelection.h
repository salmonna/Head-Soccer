


#pragma once 
#include "GameState.h"
#include "button/BaseButton.h"
//#include "gameState/Board.h"

class Board;
class SelectTeam;

class GameModeSelection:public GameState
{
public:
	GameModeSelection(Board* boardState, SelectTeam* selectTeam);

	virtual void draw(sf::RenderWindow& window) const override;
	virtual void respond(sf::Vector2f mousePressed) override;
	virtual GameState* handleEvents() override;

	virtual ~GameModeSelection();

private:

	std::vector<std::unique_ptr<BaseButton>> m_buttons;
	GameState* m_gameState;
	sf::Sprite m_Stage;
};

