#pragma once
#include <SFML/Graphics.hpp>
#include "StaticObject.h"


class ScoreBoard 
{
public:


	static ScoreBoard& getInstance() {
		static ScoreBoard instance;
		return instance;
	}

	void draw(sf::RenderWindow& window);

	void timeCalculation();
	void updateScore(int p1Points, int p2Points);

	sf::Sprite& getSprite() { return m_SpriteVec[0]; };

	bool timeIsOver();
	void reset();

	
	void resetProgress();
	bool isProcessFull();

	~ScoreBoard() = default;

private:

	ScoreBoard(const ScoreBoard&) = delete;
	ScoreBoard& operator=(const ScoreBoard&) = delete;
	ScoreBoard();


	//progress bar
	void drawProgress(sf::RenderWindow& window, std::vector<sf::Sprite> & progress);

	//time
	int m_gameTime;
	int timeCounterSec;
	int timeCounterMin;

	//clock
	sf::Clock m_clockGameTime;
	sf::Clock m_clockEverySec;
	sf::Clock m_clock;

	//text & sprite
	std::vector<sf::Text> m_textVec;
	std::vector<sf::Sprite> m_SpriteVec;
	std::vector<sf::Sprite> m_progressP1;
	std::vector<sf::Sprite> m_progressP2;

	//points
	int m_p1Points;
	int m_p2Points;

	//progress
	int m_progress;



};
