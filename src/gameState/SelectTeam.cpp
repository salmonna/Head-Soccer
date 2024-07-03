#include "gameState/SelectTeam.h"
#include "Command/SwichScreen.h"
#include "Command/Command.h"
#include "SoundControl.h"
#include "Command/Sound.h"


class GameModeSelection;
//------------------------------------------------------------- Constructor -----------------------------------
// Constructor initializes SelectTeam with necessary components
SelectTeam::SelectTeam(Controller * controller, GameModeSelection* gameMode, Board* boardState) :m_controllerPtr(controller), m_numOfPlayers(0), m_PlayerSelected(0)
, m_boardPtr(boardState)
{
	m_stage.setTexture(Resources::getInstance().getGameModeTexture()[4]);

	std::vector<sf::Texture>& tex = Resources::getInstance().getMenuTexture();

	m_buttons.push_back(std::make_unique<Button>(std::move(std::make_unique<SwichScreen>(boardState, controller)),Resources::getInstance().getSelectTeam()[7], sf::Vector2f(890.f, 777.5f))); //playButton
	m_buttons.push_back(std::make_unique<Button>(std::move(std::make_unique<SwichScreen>(gameMode, controller)), Resources::getInstance().getMenuTexture()[7], sf::Vector2f(1670.f, 45.f))); //Button 4
	m_buttons.push_back(std::make_unique<Button>(std::move(std::make_unique<Sound>(SoundControl::getInstance().getIntroSong())), tex[10], sf::Vector2f(1670.f, 145.f)));// sound button


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
// Method to initialize text for player selection
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
	std::vector<std::string> choseText{ "Select the first Player","Select the second Player",
										"Click below to start playing"};

	for (int i = 0; i < choseText.size(); i++)
	{
		m_selectText[i].setString(choseText[i]);

		if (i == 1) 
			m_selectText[i].setOutlineColor(sf::Color::Red);
		else if(i == 2)
			m_selectText[i].setOutlineColor(sf::Color::White);
	}

	setPowerText();
}
//-----------------------------------------------------------------------------
// Method to initialize text for power selection
void SelectTeam::setPowerText() {

	std::vector<std::string> powerText{ "FirePower","InvisiblePower","DragonPower",
										"FistPower","TornadoPower","DisappearPower","AvatarPower" };

	for (int i = 0; i < powerText.size(); i++)
	{
		sf::Text text = m_selectText[0];
		text.setPosition(790.f, 610.f);
		text.setOutlineColor(sf::Color(135, 206, 250));
		text.setString(powerText[i]);
		m_powerText.push_back(text);
	}
}
//-----------------------------------------------------------------------------
// Method to draw SelectTeam screen
void SelectTeam::draw(sf::RenderWindow& window) const {

	window.draw(m_stage);


	for (int i = 0; i < m_buttons.size(); i++)
	{
		if (i == 0 && m_PlayerSelected != m_numOfPlayers) {

			continue;
		}
		else
		{
			m_buttons[i]->draw(window);
		}
	}

	sf::Vector2i mouseMove = sf::Mouse::getPosition(window);

	for (int i = 0; i < m_charcters.size(); i++)
	{
		window.draw(m_charcters[i]);

		if (m_charcters[i].getGlobalBounds().contains(float(mouseMove.x), float(mouseMove.y))) {

			if (i < m_powerText.size()) {
				window.draw(m_powerText[i]);
			}
		}
	}	

	checkToDraw(window);
}
//-----------------------------------------------------------------------------
// Method to check and draw selection text based on player selection
void SelectTeam::checkToDraw(sf::RenderWindow& window) const {

	if (m_PlayerSelected < 1 || m_numOfPlayers == 1)
	{	
		if (m_PlayerSelected == 1)
			window.draw(m_selectText[2]);
		else
			window.draw(m_selectText[0]);
		
		window.draw(m_frames[0]);
	}
	else if (m_PlayerSelected >= 1  && m_numOfPlayers > 1)
	{	
		if (m_PlayerSelected >= 2)
			window.draw(m_selectText[2]);
		else
			window.draw(m_selectText[1]);

		window.draw(m_frames[0]);
		window.draw(m_frames[1]);
	}
}

//-----------------------------------------------------------------------------
// Method to respond to user interaction (mouse click)
void SelectTeam::respond(sf::Vector2f mousePressed) {
	//respond to the buttons pressed
	for (int i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i]->respond();

		if (m_buttons[i]->contains(mousePressed)) {

			if (i == 0 && m_PlayerSelected != m_numOfPlayers) {

				continue;
			}
			else
			{
				m_buttons[i]->execute();
				if (i != 2) {
					loadGameMode(i);
					reset();
				}
				break;
			}
		}
	}

	signOrPreedOnPlayers(mousePressed);
	
}

//-----------------------------------------------------------------------------
// Method to check and respond to player selection
void SelectTeam::signOrPreedOnPlayers(sf::Vector2f mousePressed) {

	for (int i = 0; i < m_charcters.size() - 1; i++)
	{
		isMouseOnPlayers(mousePressed, i);

		if (m_charcters[i].getGlobalBounds().contains(mousePressed)) {

			if (m_PlayerSelected < m_numOfPlayers) {
				m_PlayerSelected++;
				m_selectedPlayer.push_back(i);
			}
		}
	}
}
//-----------------------------------------------------------------------------
// Method to check if mouse is on specific player
void SelectTeam::isMouseOnPlayers(sf::Vector2f mousePressed, int index) {

	sf::Vector2i mouseMove = sf::Mouse::getPosition();

	if (m_charcters[index].getGlobalBounds().contains(float(mouseMove.x), float(mouseMove.y))) {

		sf::Vector2f pos = m_charcters[index].getPosition();

		if (m_PlayerSelected < 1) {

			m_frames[0].setPosition(pos.x, pos.y - 30);
		}
		else if (m_PlayerSelected == 1)
		{
			m_frames[1].setPosition(pos.x, pos.y - 30);
		}
	}
}

//-----------------------------------------------------------------------------
// Method to set number of players
void SelectTeam::setNumberOfPlayers(int Players) {

	m_numOfPlayers = Players;
}
//-----------------------------------------------------------------------------
// Method to reset player selection
void SelectTeam::reset() {

	m_selectedPlayer.clear();
	m_PlayerSelected = 0;
	for (int i = 0; i < m_frames.size(); i++)
	{
		m_frames[i].setPosition(3 * 200 - 400, 320);
	}
}
//-----------------------------------------------------------------------------
// Method to load game mode
void SelectTeam::loadGameMode(int index)
{
	if (index == 1)return;
	selectedPlayer();

	std::vector<std::string> movingObjectNames;
	switch (m_numOfPlayers)
	{
	case 1:
		movingObjectNames = { "RightPlayer", "ComputerPlayer"};
		break;
	case 2:
		movingObjectNames = { "RightPlayer", "LeftPlayer"};
		break;
	default:
		break;
	}
	m_boardPtr->createMovingObjects(movingObjectNames);
	stopSongPlayWhistle();
}
//-----------------------------------------------------------------------------
// Method to set selected player(s) in resources
void SelectTeam::selectedPlayer()
{
	for (int i = 0; i < m_selectedPlayer.size(); i++)
	{
		Resources::getInstance().setSelectedPlayer(m_selectedPlayer[i]);
	}

}
//-----------------------------------------------------------------------------
// Method to stop intro song and play whistle sound
void SelectTeam::stopSongPlayWhistle()
{
	SoundControl::getInstance().getIntroSong().pause();

	SoundControl::getInstance().getWhistle().play();

	SoundControl::getInstance().getCrowd().play();
}