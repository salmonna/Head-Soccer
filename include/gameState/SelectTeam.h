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
	void reset();
	
	void setNumberOfPlayers(int players);
private:

	void signOrPreedOnPlayers(sf::Vector2f mousePressed);
	void isMouseOnPlayers(sf::Vector2f mousePressed, int index);
	void checkToDraw(sf::RenderWindow& window) const;

	GameState* m_gameState;
	sf::Sprite m_stage;
	std::vector<sf::Sprite> m_frames;
	std::vector<std::unique_ptr<BaseButton>> m_buttons;
	std::vector<sf::Sprite> m_charcters;

	int m_numOfPlayers;
	int m_playerSelected;
};

