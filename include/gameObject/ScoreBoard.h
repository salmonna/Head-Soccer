#pragma once
#include <SFML/Graphics.hpp>
#include "StaticObject.h"


class ScoreBoard : public StaticObject
{
public:
	ScoreBoard(int gameTime);
	virtual void draw(sf::RenderWindow& window) const override;

	void timeCalculation();
	void updateScore(int p1Points, int p2Points);

	virtual sf::Sprite& getSprite() { return m_SpriteVec[0]; };

	bool timeIsOver();

	virtual ~ScoreBoard() = default;





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
