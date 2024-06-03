#pragma once
#include <SFML/Graphics.hpp>



class ScoreBoard
{
public:
	ScoreBoard(int gameTime);
	void draw(sf::RenderWindow& window);

	void timeCalculation();
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
};
