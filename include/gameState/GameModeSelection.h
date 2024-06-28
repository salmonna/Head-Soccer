


#pragma once 
#include "GameState.h"
//#include "button/BaseButton.h"
//#include "gameState/Board.h"
#include "Command/Button.h"

class Board;
class SelectTeam;
class Controller;
class Menu;

class GameModeSelection:public GameState
{
public:
	GameModeSelection(Controller * controller, Board* boardState, Menu * menu, SelectTeam* selectTeam);

	virtual void draw(sf::RenderWindow& window) const override;
	virtual void respond(sf::Vector2f mousePressed) override;
	virtual GameState * prevState() override;

	virtual ~GameModeSelection();

private:

	void loadGameMode(int gameMode);

	std::vector<std::unique_ptr<Button>> m_buttons;
	sf::Sprite m_Stage;
	Menu* m_prevState;
	Board* m_boardPtr;
	SelectTeam* m_selectTeamPtr;
};

