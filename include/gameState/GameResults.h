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

	void finalScoreResult();

	void updateWinnerMatch(int leftPlayerPoint, int rightPlayerPoint);

	void playerOrderAndSide();

	void IntiliazTextResult();

	virtual void draw(sf::RenderWindow& window) const override;
	void drawFinalResult(sf::RenderWindow& window) const;
	virtual void respond(sf::Vector2f mousePressed) override;

	~GameResults() = default;

private:
	std::vector<std::unique_ptr<Button>> m_buttons;
	std::vector<sf::Sprite> m_gameResultSprite;
	GameState* m_gameState;
	
	std::vector<sf::Text> m_resultText;
	std::vector<sf::Sprite> m_charcters;
	bool m_initilaze;
};