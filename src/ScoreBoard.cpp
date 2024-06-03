#pragma once
#include "ScoreBoard.h"
#include "Resources.h"

ScoreBoard::ScoreBoard(int gameTime) : timeCounterSec(gameTime % 60), 
timeCounterMin(gameTime / 60), m_gameTime(gameTime)
{

	std::vector<sf::Texture>& texturs = Resources::getInstance().getScoreBoardTexture();
	for (int i = 0; i < texturs.size(); i++)
	{
		auto sprite = sf::Sprite(texturs[i]);
		m_SpriteVec.push_back(sprite);
	}
	float x = 1800 / 2 -1200/2;
	m_SpriteVec[0].setPosition(x, -500);

	//font
	m_textVec.push_back(sf::Text());
	m_textVec[0].setFont(Resources::getInstance().getFont());
	m_textVec[0].setCharacterSize(50);
	m_textVec[0].setPosition(0, 0);
	

}


void ScoreBoard::draw(sf::RenderWindow& window)
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

void ScoreBoard::timeCalculation()
{
	sf::Time timeForSec = m_clockEverySec.getElapsedTime();
	float secondsForSec = timeForSec.asSeconds();


	if (timeCounterSec == 0)
	{
		--timeCounterMin;
		timeCounterSec = 59;
	}



	if (secondsForSec >= 1)
	{
		--timeCounterSec;

		std::string str = "Game Time: " + std::to_string(timeCounterMin) + ":" + std::to_string(timeCounterSec);
		m_textVec[0].setString(str);
		m_clockEverySec = sf::Clock();
	}

}


bool ScoreBoard::timeIsOver()
{
	return timeCounterSec == 1 && timeCounterMin == 0;
}