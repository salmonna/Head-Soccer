#include "gameState/SelectTeam.h"
#include "Command/SwichScreen.h"
#include "Command/Command.h"


class GameModeSelection;

SelectTeam::SelectTeam(Controller * controller, GameModeSelection* gameMode, Board* boardState) :m_controllerPtr(controller), m_numOfPlayers(0), m_playerSelected(0)
, m_BoardPtr(boardState)
{
	m_stage.setTexture(Resources::getInstance().getGameModeTexture()[0]);
	//m_buttons.push_back(std::make_unique<StartButton>(boardState,this));

	m_buttons.push_back(std::make_unique<Button>(std::move(std::make_unique<SwichScreen>(boardState, controller)), Resources::getInstance().getSelectTeam()[0], sf::Vector2f(520.f, 690.f))); //playButton
	m_buttons.push_back(std::make_unique<Button>(std::move(std::make_unique<SwichScreen>(gameMode, controller)), Resources::getInstance().getMenuTexture()[7], sf::Vector2f(0, 0))); //Button 4

	std::vector<sf::Texture>& charctersTexture = Resources::getInstance().getSelectTeam();
	
	auto sprite = sf::Sprite(charctersTexture[1]);
	sprite.setPosition(630, 50);
	m_charcters.push_back(sprite);

	auto frame = sf::Sprite(charctersTexture[2]);
	frame.setPosition(3 * 200 - 500, 270);
	m_frames.push_back(frame);
	frame.setColor(sf::Color::Red);
	m_frames.push_back(frame);

	for (int i = 3; i < charctersTexture.size(); i++)
	{
		auto sprite = sf::Sprite(charctersTexture[i]);
		sprite.scale(0.6f,0.6f);
		sprite.setPosition(i*200 - 500, 300);
		m_charcters.push_back(sprite);
	}
	
}
//-----------------------------------------------------------------------------
void SelectTeam::draw(sf::RenderWindow& window) const {

	window.draw(m_stage);


	for (int i = 0; i < m_buttons.size(); i++)
	{
		if (m_playerSelected >= m_numOfPlayers) {

			m_buttons[i]->draw(window);
		}
	}

	for (int i = 0; i < m_charcters.size(); i++)
	{
		window.draw(m_charcters[i]);
	}	

	checkToDraw(window);
}
//-----------------------------------------------------------------------------

void SelectTeam::checkToDraw(sf::RenderWindow& window) const {

	if (m_playerSelected < 1 || m_numOfPlayers == 1)
	{
		window.draw(m_frames[0]);
	}
	else if (m_playerSelected >= 1 && m_numOfPlayers > 1)
	{
		window.draw(m_frames[0]);
		window.draw(m_frames[1]);
	}

}

//-----------------------------------------------------------------------------
void SelectTeam::respond(sf::Vector2f mousePressed) {
	//respond to the buttons pressed
	for (int i = 0; i < m_buttons.size(); i++)
	{
		if (m_buttons[i]->contains(mousePressed)) {

			loadGameMode(i);
			reset();
			m_buttons[i]->execute();
			break;
		}
	}

	signOrPreedOnPlayers(mousePressed);
	
}
//-----------------------------------------------------------------------------
void SelectTeam::signOrPreedOnPlayers(sf::Vector2f mousePressed) {

	
	for (int i = 1; i < m_charcters.size(); i++)
	{
		isMouseOnPlayers(mousePressed, i);

		if (m_charcters[i].getGlobalBounds().contains(mousePressed)) {

			m_playerSelected++;
		}
	}
}
//-----------------------------------------------------------------------------

void SelectTeam::isMouseOnPlayers(sf::Vector2f mousePressed, int index) {

	sf::Vector2i mouseMove = sf::Mouse::getPosition();

	if (m_charcters[index].getGlobalBounds().contains(float(mouseMove.x), float(mouseMove.y))) {

		sf::Vector2f pos = m_charcters[index].getPosition();

		if (m_playerSelected < 1) {

			m_frames[0].setPosition(pos.x, pos.y - 30);
		}
		else if (m_playerSelected == 1)
		{
			m_frames[1].setPosition(pos.x, pos.y - 30);
		}
	}
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void SelectTeam::setNumberOfPlayers(int players) {

	m_numOfPlayers = players;
}
//-----------------------------------------------------------------------------
void SelectTeam::reset() {

	m_playerSelected = 0;
	for (int i = 0; i < m_frames.size(); i++)
	{
		m_frames[i].setPosition(3 * 200 - 500, 270);
	}
}


void SelectTeam::loadGameMode(int index)
{
	if (index == 1)return;

	std::vector<std::string> movingObjectNames;
	std::vector<std::string> staticObjectNames;
	switch (m_numOfPlayers)
	{
	case 1:
		movingObjectNames = { "RightPlayer", "ComputerPlayer", "Ball" };
		break;
	case 2:
		movingObjectNames = { "RightPlayer", "LeftPlayer", "Ball" };
		break;
	default:
		return; //undo
		break;
	}
	staticObjectNames = { "LeftOutsideGoalSide" , "RightOutsideGoalSide" };
	m_BoardPtr->createMovingObjects(movingObjectNames);
	m_BoardPtr->createStaticObjects(staticObjectNames);
}



SelectTeam::~SelectTeam()
{
}