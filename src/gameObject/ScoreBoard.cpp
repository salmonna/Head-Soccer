#pragma once
#include "gameObject/ScoreBoard.h"
#include "Resources.h"
#include "FileException.h"
#include <exception>
#include "SoundControl.h"
//----------------------------------------------------------------------
// Constructor initializes ScoreBoard object
ScoreBoard::ScoreBoard() :m_gameTime(5), timeCounterSec(m_gameTime % 60),
timeCounterMin(m_gameTime / 60), m_p1Points(0), m_p2Points(0), m_progressP1(0), m_progressP2(0), m_goalSign(false)
,m_startOfGame(true)
{
	try {
		defineScoreBoardTexture();
		defineScoreBoardText();
		defineProgressTexture();

	}
	catch (const std::exception&) {
		throw FileException("Deviation from the arrays in funcs:defineScoreBoardTexture/ scoreBoardText/  defineProgressTexture");
	};
}
//----------------------------------------------------------------------
// Define textures for the score board sprites
void ScoreBoard::defineScoreBoardTexture()
{

	std::vector<sf::Texture>& texturs = Resources::getInstance().getScoreBoardTexture();
	for (int i = 0; i < texturs.size()-2; i++)
	{
		auto sprite = sf::Sprite(texturs[i]);
		m_SpriteVec.push_back(sprite);
	}

	//--------------------goal sign------------------------------//
	m_goalSprite.setTexture(texturs[1]);
	m_goalSprite.setPosition(50, 200);
	m_kickOffSprite.setTexture(texturs[2]);
	m_kickOffSprite.setPosition(50,200);

	sf::Font & font = Resources::getInstance().getFont();
	for (int i = 0; i < 3; i++)
	{
		m_textVec.push_back(sf::Text());
		m_textVec[i].setFont(font);
		m_textVec[i].setCharacterSize(70);
		m_textVec[i].setFillColor(sf::Color::White);
	}

	m_SpriteVec[0].setPosition(300.f, -500);
}
//----------------------------------------------------------------------
// Define textures for the progress bar sprites
void ScoreBoard::defineProgressTexture()
{
	std::vector<sf::Texture>& texture = Resources::getInstance().getPowerTexture();

	sf::Vector2f pos1 = sf::Vector2f(550, 80);
	sf::Vector2f pos2 = sf::Vector2f(950, 80);
	sf::Vector2f factor(2.8f, 3.5f);

	for (int i = 0; i < texture.size(); i++)
	{
		m_progressP1Sprite.push_back(sf::Sprite(texture[i]));
		m_progressP1Sprite[i].scale(0.6f, 1.f);
		m_progressP1Sprite[i].setPosition(pos1);

		m_progressP2Sprite.push_back(sf::Sprite(texture[i]));
		m_progressP2Sprite[i].scale(0.6f, 1.f);
		m_progressP2Sprite[i].setPosition(pos2);
	}

	pos1 += factor;
	pos2 += factor;

	m_progressP1Sprite[1].setPosition(pos1);
	m_progressP2Sprite[1].setPosition(pos2);
}
//----------------------------------------------------------------------
// Define text positions for the score board
void ScoreBoard::defineScoreBoardText()
{

	sf::Font& font = Resources::getInstance().getFont();
	for (int i = 0; i < 3; i++)
	{
		m_textVec.push_back(sf::Text());
		m_textVec[i].setFont(font);
		m_textVec[i].setCharacterSize(70);
		m_textVec[i].setFillColor(sf::Color::White);
	}


	//font time pos
	m_textVec[0].setPosition(875.f, 0.f);

	//font points pos
	m_textVec[1].setPosition(475.f, 50.f);
	m_textVec[2].setPosition(1305.f, 50.f);
}
//----------------------------------------------------------------------
// Draw function to render ScoreBoard objects on the window
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

	for (int i = 0; i < m_flags.size(); i++)
	{
		window.draw(m_flags[i]);
	}
  
	if (m_goalSign)
		window.draw(m_goalSprite);
	if (m_startOfGame)
		window.draw(m_kickOffSprite);

}
//----------------------------------------------------------------------
// Update progress bars for both players
void ScoreBoard::Progress()
{
	float seconds = m_clock.getElapsedTime().asSeconds();
	updateProgress(m_progressP1Sprite, m_progressP1, seconds);
	updateProgress(m_progressP2Sprite, m_progressP2, seconds);
	
	if (m_goalSign)
		m_goalSprite.move(10.f, 0.f);

	if (m_clockGoalSign.getElapsedTime().asSeconds() > 2.f)
	{
		m_goalSign = false;
		m_goalSprite.setPosition(0.f, 200.f);
	}

}

//----------------------------------------------------------------------
// Update progress for a given set of progress sprites
void ScoreBoard::updateProgress(std::vector<sf::Sprite>& progressSprite, int & progress, float seconds)
{
	int width = (progress + 1) * 8;

	if (seconds >= 0.2f && width < 590)
	{
		progress++;
		m_clock.restart();
	}


	try {
		sf::IntRect characterRect(0, 0, width, int(progressSprite[1].getGlobalBounds().height));
		progressSprite[1].setTextureRect(characterRect);
	}
	catch (const std::exception&) {
		throw FileException("Deviation from the array: progressSprite");
	}


}
//----------------------------------------------------------------------
// Check if progress bar for player 1 is full
bool ScoreBoard::isProgressP1Full() const {

	int progress = (m_progressP1 + 1) * 8;

	return progress > 490;
}
//----------------------------------------------------------------------
// Check if progress bar for player 2 is full
bool ScoreBoard::isProgressP2Full() const {
	int progress = (m_progressP2 + 1) * 8;

	return progress > 490;
}
//----------------------------------------------------------------------
// Reset progress bar for player 1
void ScoreBoard::resetProgressP1()
{
	m_progressP1 = 0;
}
//----------------------------------------------------------------------
// Reset progress bar for player 2
void ScoreBoard::resetProgressP2()
{
	m_progressP2 = 0;
}



//========================Time=======================
// Calculate and update time display on the score board
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
		try {
			m_textVec[0].setString(str);
		}
		catch (const std::exception&) {
			throw FileException("Deviation from the array: m_textVec");
		}
		m_clockEverySec = sf::Clock();
	}

}
//----------------------------------------------------------------------
// Check if game time is over
bool ScoreBoard::timeIsOver()
{
	if (timeCounterSec == 0 && timeCounterMin == 0) {

		SoundControl::getInstance().getWhistle().play(); // play whistle sound
		SoundControl::getInstance().getCrowd().pause(); // pause crowd sound
		SoundControl::getInstance().getGoalSound().pause();// pause goal sound
		return true;
	}
	return false;
}


//----------------------------------------------------------------------
// Reset all score board data and progress
void ScoreBoard::reset()
{
	timeCounterMin = m_gameTime / 60;
	timeCounterSec = m_gameTime % 60;
	m_p1Points = 0, m_p2Points = 0;

	m_flags.clear();
	m_startOfGame = true;
	resetProgressP1();
	resetProgressP2();
}

//=======================Points=======================
// Update scores for both players and handle goal sign display
void ScoreBoard::updateScore(int p1Points, int p2Points)
{
	if (p1Points != 0 && p2Points != 0){
		m_goalSign = true;
		m_clockGoalSign.restart();
	}

	m_p1Points += p1Points;
	m_p2Points += p2Points;

	try {
		std::string str = std::to_string(m_p1Points);
		m_textVec[1].setString(str);

		str = std::to_string(m_p2Points);
		m_textVec[2].setString(str);
	}
	catch (const std::exception&) {
		throw FileException("Deviation from the array");
	}

	if (m_startOfGame) {
		m_kickOffSprite.move(10.f, 0.f);
	}
	if (m_clockGameTime.getElapsedTime().asSeconds() > 2.f)
	{
		m_startOfGame = false;
		m_kickOffSprite.setPosition(0.f, 200.f);
	}
}
//----------------------------------------------------------------------
// Get points for a specified player
int ScoreBoard::getPoint(int num) const{

	if (num == 1) {
		return m_p1Points;
	}
	return m_p2Points;
}


//========================goalSign======================//
// Check if a goal has been scored
bool ScoreBoard::isGoal() const {
	return m_goalSign;
}
//----------------------------------------------------------------------
// Set goal sign to indicate a goal has been scored
void ScoreBoard::setGoalSign() {
	m_goalSign = true;
	m_clockGoalSign.restart();
}
//----------------------------------------------------------------------
// Set flags for players based on their order
void ScoreBoard::setFlagsPlayers() {

	std::vector<int> Players = Resources::getInstance().getPlayerOrder();

	for (int i = 0; i < Players.size(); i++)
	{
		int index = Resources::getInstance().getPlayerOrder()[i];
		auto sprite = sf::Sprite(Resources::getInstance().getCountriesFlags()[index]);
		sprite.scale(0.5, 0.5);
		m_flags.push_back(sprite);
	}

	try {
		m_flags[0].setPosition(1250.f, 165.f);
		m_flags[1].setPosition(435.f, 165.f);
	}
	catch (const std::exception&) {
		throw FileException("Deviation from the array: m_flags");
	}

}
//----------------------------------------------------------------------
// Get vector of flags for players
std::vector<sf::Sprite>& ScoreBoard::getFlags() {
	return m_flags;
}

//----------------------------------------------------------------------
// Get score board sprite
sf::Sprite& ScoreBoard::getSprite() {
	return m_SpriteVec[0]; 
};

