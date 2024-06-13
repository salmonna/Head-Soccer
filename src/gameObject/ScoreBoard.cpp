#pragma once
#include "gameObject/ScoreBoard.h"
#include "Resources.h"

ScoreBoard::ScoreBoard(int gameTime) : timeCounterSec(gameTime % 60), 
timeCounterMin(gameTime / 60), m_gameTime(gameTime), m_p1Points(0), m_p2Points(0)
{

	std::vector<sf::Texture>& texturs = Resources::getInstance().getScoreBoardTexture();
	for (int i = 0; i < texturs.size(); i++)
	{
		auto sprite = sf::Sprite(texturs[i]);
		m_SpriteVec.push_back(sprite);
	}
	float x = 1800 / 2 -1200/2;
	m_SpriteVec[0].setPosition(x, -500);


	sf::Font & font = Resources::getInstance().getFont();
	for (int i = 0; i < 3; i++)
	{
		m_textVec.push_back(sf::Text());
		m_textVec[i].setFont(font);
		m_textVec[i].setCharacterSize(70);
		m_textVec[i].setFillColor(sf::Color::White);


	}

	//font time pos
	m_textVec[0].setPosition(875, 0);

	//font points pos
	m_textVec[1].setPosition(x+175, 50);
	m_textVec[2].setPosition(x + 1200-175-20, 50);
	

}


void ScoreBoard::draw(sf::RenderWindow & window) const
{
	for (int i = 0; i < m_SpriteVec.size(); i++)
	{
		window.draw(m_SpriteVec[i]);
	}

	
	for (int i = 0; i < m_textVec.size(); i++)
	{
		window.draw(m_textVec[i]);
	}
}


//========================Time=======================
void ScoreBoard::timeCalculation()
{
	sf::Time timeForSec = m_clockEverySec.getElapsedTime();
	float secondsForSec = timeForSec.asSeconds();


	if (timeCounterSec == 0 && timeCounterMin > 0)
	{
		--timeCounterMin;
		timeCounterSec = 59;
	}



	if (secondsForSec >= 1 && timeCounterSec > 0)
	{
		std::string str = std::to_string(timeCounterMin) + ":" + std::to_string(timeCounterSec);
		--timeCounterSec;
		m_textVec[0].setString(str);
		m_clockEverySec = sf::Clock();
	}

}
bool ScoreBoard::timeIsOver()
{
	if (timeCounterSec == 0 && timeCounterMin == 0) {

		timeCounterMin = m_gameTime/60;
		timeCounterMin = m_gameTime%60;
		return true;
	}
	return false;
}

//=======================Points=======================
void ScoreBoard::updateScore(int p1Points, int p2Points)
{
	m_p1Points += p1Points;
	m_p2Points += p2Points;

	std::string str = std::to_string(m_p1Points);
	m_textVec[1].setString(str);

	str = std::to_string(m_p2Points);
	m_textVec[2].setString(str);
}