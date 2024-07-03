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


	bool timeIsOver();
	void reset();

	//progress bar
	void Progress();
	void resetProgressP1();
	void resetProgressP2();
	bool isProgressP1Full() const;
	bool isProgressP2Full() const;

	//goal
	bool isGoal() const;
	void setGoalSign();
	void setFlagsPlayers();

	//get
	int getPoint(int num) const;
	std::vector<sf::Sprite>& getFlags();
	sf::Sprite& getSprite();


private:

	ScoreBoard(const ScoreBoard&) = delete;
	ScoreBoard& operator=(const ScoreBoard&) = delete;

	ScoreBoard();
	~ScoreBoard() = default;


	//difine
	void defineScoreBoardTexture();
	void defineProgressTexture();
	void defineScoreBoardText();

	//update
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
	std::vector<sf::Sprite> m_flags;
	sf::Sprite m_goalSprite;

	//sound
	sf::Sound m_whistle;
	
	//points
	int m_p1Points;
	int m_p2Points;

	//progress
	int m_progressP1;
	int m_progressP2;

};
