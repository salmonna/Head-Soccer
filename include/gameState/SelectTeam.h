#pragma once 
#include "GameState.h"
#include "gameState/Board.h"
#include "Command/Button.h"

class Controller;


class SelectTeam : public GameState
{
public:
	SelectTeam(Controller* controller, Board* boardState);
	void selectTextPlayer();
	virtual ~SelectTeam();

	virtual void draw(sf::RenderWindow& window) const override;
	virtual void respond(sf::Vector2f mousePressed) override;	
	void setNumberOfPlayers(int players);
	void loadGameObject();
private:

	void signOrPreedOnPlayers(sf::Vector2f mousePressed);
	void isMouseOnPlayers(sf::Vector2f mousePressed, int index);
	void checkToDraw(sf::RenderWindow& window) const;
	void reset();


	GameState* m_gameState;
	Board* m_boardPtr;
	sf::Sprite m_stage;
	std::vector<sf::Sprite> m_frames;
	Controller* m_controllerPtr;
	//std::vector<std::unique_ptr<BaseButton>> m_buttons;

	std::vector<std::unique_ptr<Button>> m_buttons;

	std::vector<sf::Sprite> m_charcters;
	std::vector<sf::Text> m_selectText;
	int m_numOfPlayers;
	int m_playerSelected;
};

