#pragma once
#include <SFML/Graphics.hpp>
#include "StaticObject.h"
#include <SFML/Audio.hpp>


class ScoreBoard 
{
public:


	static ScoreBoard& getInstance() {
		static ScoreBoard instance;
		return instance;
	}

	void draw(sf::RenderWindow& window) const ;

	void timeCalculation();
	void updateScore(int p1Points, int p2Points);

	sf::Sprite& getSprite() { return m_SpriteVec[0]; };

	bool timeIsOver();
	void reset();

	
	void resetProgressP1();
	void resetProgressP2();

	bool istProgressP1Full();
	bool istProgressP2Full();

	//progress bar
	void Progress();
	bool isGoal();
	void setGoalSign();

	int getPoint(int num);


	void setFlagsPlayers();
	std::vector<sf::Sprite>& getFlags();

	~ScoreBoard() = default;

private:
	ScoreBoard(const ScoreBoard&) = delete;
	ScoreBoard& operator=(const ScoreBoard&) = delete;
	ScoreBoard();

	void defineScoreBoardTexture();

	void defineProgressTexture();

	void scoreBoardText();

	void updateProgress(std::vector<sf::Sprite>& progressSprite, int& progress, float seconds);

	//goalSign
	bool m_goalSign;

	//time
	int m_gameTime;
	int timeCounterSec;
	int timeCounterMin;

	//clock
	sf::Clock m_clockGameTime;
	sf::Clock m_clockEverySec;
	sf::Clock m_clock;
	sf::Clock m_clockGoalSign;

	//text & sprite
	std::vector<sf::Text> m_textVec;
	std::vector<sf::Sprite> m_SpriteVec;
	std::vector<sf::Sprite> m_progressP1Sprite;
	std::vector<sf::Sprite> m_progressP2Sprite;

	sf::Sprite m_goalSprite;

	std::vector<sf::Sprite> m_flags;
	
	//points
	int m_p1Points;
	int m_p2Points;

	//progress
	int m_progressP1;
	int m_progressP2;

};
