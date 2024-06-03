#pragma once
#include <SFML/Graphics.hpp>



class ScoreBoard
{
public:
	ScoreBoard(int gameTime);
	void draw(sf::RenderWindow& window);

	void timeCalculation();
	void updateScore(int p1Points, int p2Points);

	bool timeIsOver();

	~ScoreBoard() = default;

private:

	//time
	int m_gameTime;
	int timeCounterSec;
	int timeCounterMin;
	sf::Clock m_clockGameTime;
	sf::Clock m_clockEverySec;

	//text & sprite
	std::vector<sf::Text> m_textVec;
	std::vector<sf::Sprite> m_SpriteVec;

	//points
	int m_p1Points;
	int m_p2Points;


};
