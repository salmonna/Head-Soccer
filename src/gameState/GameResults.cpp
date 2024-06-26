#include "gameState/GameResults.h"
#include "Resources.h"
#include "Command/SwichScreen.h"
#include "Command/Command.h"

//gameResults constactor
GameResults::GameResults(Controller* controller, Menu* menuState): m_gameState(NULL),m_initilaze(false)
{
	std::vector<sf::Texture>& texture = Resources::getInstance().getGameModeTexture();
	m_sprite.setTexture(texture[0]);

	std::vector<sf::Texture>& texture2 = Resources::getInstance().getPauseTexture();
	m_buttons.push_back(std::make_unique<Button>(std::move(std::make_unique<SwichScreen>(menuState, controller)),
															texture2[2], sf::Vector2f(845.f, 900.f))); //exit to menu Button

	IntiliazTextResult();

	int leftPlayerPoint = ScoreBoard::getInstance().getPoint(1);
	int rightPlayerPoint = ScoreBoard::getInstance().getPoint(0);

	std::string score = std::to_string(leftPlayerPoint) + "     -     " + std::to_string(rightPlayerPoint);
	m_resultText[1].setString(score);
	
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
			m_resultText[i].setPosition(750, 10);

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

			m_initilaze = false;
			m_gameResultSprite.clear();
			return;
		}
	}

	if (!m_initilaze) {
		playerOrderAndSide();
	}
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
		m_gameResultSprite.push_back(sprite);
	}

	m_gameResultSprite[0].setPosition(1320, 350);
	m_gameResultSprite[0].scale(-1, 1);

	if (playerOrder.size() == 2) {

		m_gameResultSprite[1].setPosition(400, 350);

	}

	Resources::getInstance().resetPlayerOrder();
	m_initilaze = true;
}
//----------------------------------------------------------------------------------
//draw function
void GameResults::draw(sf::RenderWindow& window) const
{

	window.draw(m_sprite);
	
	//respond to the buttons pressed
	for (int i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i]->draw(window);
	}

	for (int i = 0; i < m_resultText.size(); i++)
	{
		window.draw(m_resultText[i]);
	}

	for (int i = 0; i < m_gameResultSprite.size(); i++)
	{
		window.draw(m_gameResultSprite[i]);
	}
}
