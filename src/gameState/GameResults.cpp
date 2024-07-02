#include "gameState/GameResults.h"
#include "Resources.h"
#include "Command/SwichScreen.h"
#include "Command/Command.h"
#include "gameObject/ScoreBoard.h"
#include <exception>
#include "FileException.h"
#include "SoundControl.h"
#include "Command/Sound.h"

//gameResults constactor
GameResults::GameResults(Controller* controller, Menu* menuState): m_gameState(NULL),m_initilaze(false)
{
	auto sprite = sf::Sprite(Resources::getInstance().getGameModeTexture()[4]);
	m_gameResultSprite.push_back(sprite);
	

	std::vector<sf::Texture>& texture2 = Resources::getInstance().getPauseTexture();
	m_buttons.push_back(std::make_unique<Button>(std::move(std::make_unique<SwichScreen>(menuState, controller)),
															texture2[2], sf::Vector2f(750.f, 750.f))); //exit to menu Button

	std::vector<sf::Texture>& tex = Resources::getInstance().getMenuTexture();

	m_buttons.push_back(std::make_unique<Button>(std::move(std::make_unique<Sound>(SoundControl::getInstance().getIntroSong())), tex[10], sf::Vector2f(0.f, 0.f)));

	IntiliazTextResult();

}


//----------------------------------------------------------------------------------
void GameResults::IntiliazTextResult()
{
	sf::Font& font = Resources::getInstance().getFont();

	for (int i = 0; i < 2; i++)
	{
		m_resultText.push_back(sf::Text());
		m_resultText[i].setFont(font);

		if (i == 0) {

			m_resultText[i].setString("Result");
			m_resultText[i].setOutlineColor(sf::Color::Black);
			m_resultText[i].setOutlineThickness(10.f);
			m_resultText[i].setCharacterSize(200);
			m_resultText[i].setPosition(750, 0);

			continue;
		}

		m_resultText[i].setFillColor(sf::Color::White);
		m_resultText[i].setCharacterSize(150);
		m_resultText[i].setPosition(720, 450);
	}
}
//----------------------------------------------------------------------------------
//respond function check if there is a click on the exit button
void GameResults::respond(sf::Vector2f mousePressed)
{
	//respond to the buttons pressed
	for (int i = 0; i < m_buttons.size(); i++)
	{
		if (m_buttons[i]->contains(mousePressed)) {

			m_buttons[i]->execute();

			if (i == 0) {
				resetGameResult();
				return;
			}
		}
	}

	if (!m_initilaze) {

		playerOrderAndSide();
		finalScoreResult();
		SoundControl::getInstance().getIntroSong().play();
		
	}
}
//----------------------------------------------------------------------------------
void GameResults::resetGameResult()
{	
	m_initilaze = false;
	m_charcters.clear();
	m_flags.clear();
	ScoreBoard::getInstance().reset();
	m_gameResultSprite.erase(m_gameResultSprite.begin() + 1 , m_gameResultSprite.end());
}
//----------------------------------------------------------------------------------
void GameResults::playerOrderAndSide()
{	
	//set player oreder and sides
	auto playerOrder = Resources::getInstance().getPlayerOrder();
	auto sprite = sf::Sprite();

	for (int i = 0; i < playerOrder.size(); i++)
	{
		int index = playerOrder[i];
		sprite.setTexture(Resources::getInstance().getSelectTeam()[index]);
		m_charcters.push_back(sprite);
	}

	m_charcters[0].setPosition(1320.f, 350.f);
	m_charcters[0].scale(-1, 1);
	m_charcters[1].setPosition(400.f, 350.f);

	m_flags = ScoreBoard::getInstance().getFlags();
	m_flags[0].setPosition(1080.f, 675.f);
	m_flags[1].setPosition(530.f, 675.f);
	Resources::getInstance().resetPlayerOrder();
	m_initilaze = true;
}
//----------------------------------------------------------------------------------
void GameResults::finalScoreResult()
{
	int leftPlayerPoint = ScoreBoard::getInstance().getPoint(1);
	int rightPlayerPoint = ScoreBoard::getInstance().getPoint(0);

	std::string score = std::to_string(leftPlayerPoint) + "     -     " + std::to_string(rightPlayerPoint);
	m_resultText[1].setString(score);

	updateWinnerMatch(leftPlayerPoint, rightPlayerPoint);
	
}
//----------------------------------------------------------------------------------
void GameResults::updateWinnerMatch(int leftPlayerPoint, int rightPlayerPoint)
{
	auto sprite = sf::Sprite();

	if (leftPlayerPoint != rightPlayerPoint) {
		sprite.setTexture(Resources::getInstance().gameResultsTexture()[2]);
		sprite.scale(0.2f, 0.2f);
		m_gameResultSprite.push_back(sprite);

		if (leftPlayerPoint > rightPlayerPoint) {

			m_charcters[0].setColor(sf::Color(128, 128, 128));
			m_gameResultSprite[1].setPosition(450, 200);
		}
		else if (rightPlayerPoint > leftPlayerPoint) {

			m_charcters[1].setColor(sf::Color(128, 128, 128));
			m_gameResultSprite[1].setPosition(1020, 200);
		}
	}
	else {
		sprite.setTexture(Resources::getInstance().gameResultsTexture()[3]);
		sprite.scale(0.15f, 0.15f);
		m_gameResultSprite.push_back(sprite);
		m_gameResultSprite[1].setPosition(770, 220);
	}
}
//----------------------------------------------------------------------------------
//draw function
void GameResults::draw(sf::RenderWindow& window) const
{

	//window.draw(m_sprite);
	for (int i = 0; i < m_gameResultSprite.size(); i++)
	{
		window.draw(m_gameResultSprite[i]);
	}

	//respond to the buttons pressed
	for (int i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i]->draw(window);
	}

	drawFinalResult(window);
}
//----------------------------------------------------------------------------------
void GameResults::drawFinalResult(sf::RenderWindow& window) const
{
	for (int i = 0; i < m_resultText.size(); i++)
	{
		window.draw(m_resultText[i]);
	}

	for (int i = 0; i < m_charcters.size(); i++)
	{
		window.draw(m_charcters[i]);
	}

	for (int i = 0; i < m_flags.size(); i++)
	{
		window.draw(m_flags[i]);
	}
}
