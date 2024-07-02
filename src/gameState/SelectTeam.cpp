#include "gameState/SelectTeam.h"
#include "Command/SwichScreen.h"
#include "Command/Command.h"
#include "SoundControl.h"
#include "Command/Sound.h"



class GameModeSelection;

SelectTeam::SelectTeam(Controller * controller, GameModeSelection* gameMode, Board* boardState) :m_controllerPtr(controller), m_numOfPlayers(0), m_playerSelected(0)
, m_boardPtr(boardState)
{
	m_stage.setTexture(Resources::getInstance().getGameModeTexture()[4]);

	std::vector<sf::Texture>& tex = Resources::getInstance().getMenuTexture();

	m_buttons.push_back(std::make_unique<Button>(std::move(std::make_unique<SwichScreen>(boardState, controller)),Resources::getInstance().getSelectTeam()[7], sf::Vector2f(520.f, 690.f))); //playButton
	m_buttons.push_back(std::make_unique<Button>(std::move(std::make_unique<SwichScreen>(gameMode, controller)), Resources::getInstance().getMenuTexture()[7], sf::Vector2f(0, 0))); //Button 4

	m_buttons.push_back(std::make_unique<Button>(std::move(std::make_unique<Sound>(SoundControl::getInstance().getIntroSong())), tex[10], sf::Vector2f(0.f, 100.f)));

	std::vector<sf::Texture>& charctersTexture = Resources::getInstance().getSelectTeam();

	auto frame = sf::Sprite(charctersTexture[9]);
	frame.setPosition(3 * 200 - 400, 320);
	m_frames.push_back(frame);
	frame.setColor(sf::Color::Red);
	m_frames.push_back(frame);

	for (int i = 0; i < charctersTexture.size() - 3; i++)
	{
		auto sprite = sf::Sprite(charctersTexture[i]);
		sprite.scale(0.6f,0.6f);
		sprite.setPosition((i+3)*200 - 400, 350);
		m_charcters.push_back(sprite);
	}

	auto sprite = sf::Sprite(charctersTexture[8]);
	sprite.setPosition(630, 20);
	m_charcters.push_back(sprite);

	selectTextPlayer();
}
//-----------------------------------------------------------------------------
void SelectTeam::selectTextPlayer()
{
	sf::Font& font = Resources::getInstance().getFont();
	for (int i = 0; i < 3; i++)
	{
		m_selectText.push_back(sf::Text());
		m_selectText[i].setFont(font);
		m_selectText[i].setPosition(650, 150);
		m_selectText[i].setCharacterSize(90);
		m_selectText[i].setFillColor(sf::Color::Black);
		m_selectText[i].setStyle(sf::Text::Bold);
		// Adding an outline to the text
		m_selectText[i].setOutlineColor(sf::Color::Green);
		m_selectText[i].setOutlineThickness(5);
	}
	m_selectText[0].setString("Select the first player");
	m_selectText[1].setString("Select the second player");
	m_selectText[1].setOutlineColor(sf::Color::Red);
	m_selectText[2].setString("Click below to start playing");
	m_selectText[2].setOutlineColor(sf::Color::White);
}
//-----------------------------------------------------------------------------
void SelectTeam::draw(sf::RenderWindow& window) const {

	window.draw(m_stage);


	for (int i = 0; i < m_buttons.size(); i++)
	{
		if (i == 0 && m_playerSelected != m_numOfPlayers) {

			continue;
		}
		else
		{
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
		if (m_playerSelected == 1)
			window.draw(m_selectText[2]);
		else
			window.draw(m_selectText[0]);
		
		window.draw(m_frames[0]);
	}
	else if (m_playerSelected >= 1  && m_numOfPlayers > 1)
	{	
		if (m_playerSelected >= 2)
			window.draw(m_selectText[2]);
		else
			window.draw(m_selectText[1]);

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

			if (i == 0 && m_playerSelected != m_numOfPlayers) {

				continue;
			}
			else if (i == 2) {
				m_buttons[i]->execute();
			}
			else
			{
				m_buttons[i]->execute();
				loadGameMode(i);
				reset();
				
				break;
			}
		}
	}

	signOrPreedOnPlayers(mousePressed);
	
}

//-----------------------------------------------------------------------------
void SelectTeam::signOrPreedOnPlayers(sf::Vector2f mousePressed) {

	
	for (int i = 0; i < m_charcters.size() - 1; i++)
	{
		isMouseOnPlayers(mousePressed, i);

		if (m_charcters[i].getGlobalBounds().contains(mousePressed)) {

			if (m_playerSelected < m_numOfPlayers) {
				m_playerSelected++;
				m_selectedPlayer.push_back(i);
			}
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

void SelectTeam::setNumberOfPlayers(int players) {

	m_numOfPlayers = players;
}
//-----------------------------------------------------------------------------
void SelectTeam::reset() {

	m_selectedPlayer.clear();
	m_playerSelected = 0;
	for (int i = 0; i < m_frames.size(); i++)
	{
		m_frames[i].setPosition(3 * 200 - 400, 320);
	}
}
//-----------------------------------------------------------------------------
void SelectTeam::loadGameMode(int index)
{
	if (index == 1)return;

	selectedPlayer();

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
		break;
	}
	staticObjectNames = { "LeftOutsideGoalSide" , "RightOutsideGoalSide" };
	ScoreBoard::getInstance().loadPlayersFlag();
	m_boardPtr->createMovingObjects(movingObjectNames);
	m_boardPtr->createStaticObjects(staticObjectNames);
	stopSongPlayWhistle();
	
	
}
//-----------------------------------------------------------------------------
void SelectTeam::selectedPlayer()
{
	for (int i = 0; i < m_selectedPlayer.size(); i++)
	{
		Resources::getInstance().setSelectedPlayer(m_selectedPlayer[i]);
	}
}
//-----------------------------------------------------------------------------
void SelectTeam::stopSongPlayWhistle()
{

	SoundControl::getInstance().getIntroSong().pause();

	SoundControl::getInstance().getWhistle().play();

	SoundControl::getInstance().getCrowd().play();

}

//-----------------------------------------------------------------------------

SelectTeam::~SelectTeam()
{
}