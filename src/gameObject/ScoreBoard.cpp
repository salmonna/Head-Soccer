#pragma once
#include "gameObject/ScoreBoard.h"
#include "Resources.h"


ScoreBoard::ScoreBoard() :m_gameTime(20), timeCounterSec(m_gameTime % 60),
timeCounterMin(m_gameTime / 60), m_p1Points(0), m_p2Points(0), m_progressP1(0), m_progressP2(0)
{

	std::vector<sf::Texture>& texturs = Resources::getInstance().getScoreBoardTexture();
	for (int i = 0; i < texturs.size(); i++)
	{
		auto sprite = sf::Sprite(texturs[i]);
		m_SpriteVec.push_back(sprite);
	}
	float x = 300.f;
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
	m_textVec[2].setPosition(x + 1005, 50);


	std::vector<sf::Texture>& texture = Resources::getInstance().getPowerTexture();

	sf::Vector2f pos = sf::Vector2f(550, 80);

	for (int i = 0; i < texture.size(); i++)
	{
		m_progressP1Sprite.push_back(sf::Sprite());
		m_progressP1Sprite[i].setTexture(texture[i]);
		m_progressP1Sprite[i].scale(0.6, 1);
		m_progressP1Sprite[i].setPosition(pos);
	}

	pos.y += 3.5;
	pos.x += 2.8f;
	m_progressP1Sprite[1].setPosition(pos);

	pos = sf::Vector2f(950, 80);

	for (int i = 0; i < texture.size(); i++)
	{
		m_progressP2Sprite.push_back(sf::Sprite());
		m_progressP2Sprite[i].setTexture(texture[i]);
		m_progressP2Sprite[i].scale(0.6, 1);
		m_progressP2Sprite[i].setPosition(pos);
	}
	pos.y += 3.5;
	pos.x += 2.8f;
	m_progressP2Sprite[1].setPosition(pos);


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


	for (int i = 0; i < 2; i++)
	{
		window.draw(m_progressP1Sprite[i]);
		window.draw(m_progressP2Sprite[i]);
	} 
}


void ScoreBoard::Progress()
{
	float seconds = m_clock.getElapsedTime().asSeconds();
	ScoreBoard::getInstance().updateProgress(m_progressP1Sprite, m_progressP1, seconds);
	ScoreBoard::getInstance().updateProgress(m_progressP2Sprite, m_progressP2, seconds);

}



void ScoreBoard::updateProgress(std::vector<sf::Sprite>& progressSprite, int & progress, float seconds)
{
	int width = (progress + 1) * 8;

	if (seconds >= 0.1 && width < 490)
	{
		progress++;
		m_clock.restart();
	}

	sf::IntRect characterRect(0, 0, width, progressSprite[1].getGlobalBounds().height);
	progressSprite[1].setTextureRect(characterRect);
}


bool ScoreBoard::istProgressP1Full() {
	return (m_progressP1 + 1) * 8 > 490;
}

bool ScoreBoard::istProgressP2Full() {
	return (m_progressP2 + 1) * 8 > 490;
}


void ScoreBoard::resetProgressP1()
{
	m_progressP1 = 0;
}

void ScoreBoard::resetProgressP2()
{
	m_progressP2 = 0;
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
		return true;
	}
	return false;
}



void ScoreBoard::reset()
{
	timeCounterMin = m_gameTime / 60;
	timeCounterSec = m_gameTime % 60;
	m_p1Points = 0, m_p2Points = 0;
	resetProgressP1();
	resetProgressP2();
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

int ScoreBoard::getPoint(int num) {

	if (num == 1) {
		return m_p1Points;
	}
	return m_p2Points;
}