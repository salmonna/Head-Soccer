
#include "gameState/GameModeSelection.h"
#include "Resources.h"
#include "Command/SwichScreen.h"
#include "Command/Command.h"

GameModeSelection::GameModeSelection(Controller* controller, Board* boardState, Menu* menu, SelectTeam* selectTeam):m_boardPtr(boardState), m_selectTeamPtr(selectTeam)
{
	std::vector<sf::Texture>& texture = Resources::getInstance().getGameModeTexture();
	m_Stage.setTexture(texture[0]);

	m_buttons.push_back(std::make_unique<Button>(std::move(std::make_unique<SwichScreen>(menu, controller)), Resources::getInstance().getMenuTexture()[7], sf::Vector2f(0, 0))); //Button 4
	m_buttons.push_back(std::make_unique<Button>(std::move(std::make_unique<SwichScreen>(selectTeam, controller)), texture[1], sf::Vector2f(350.f, 150.f))); //Button 1
	m_buttons.push_back(std::make_unique<Button>(std::move(std::make_unique<SwichScreen>(selectTeam, controller)), texture[2], sf::Vector2f(800.f, 150.f))); //Button 2
	m_buttons.push_back(std::make_unique<Button>(std::move(std::make_unique<SwichScreen>(selectTeam, controller)), texture[3], sf::Vector2f(1250.f, 150.f))); //Button 3

	textModeSelection();
}
//-------------------------------------------------------------
void GameModeSelection::textModeSelection()
{
	sf::Font& font = Resources::getInstance().getFont();

	for (int i = 0; i < 3; i++)
	{
		m_modeText.push_back(sf::Text());
		m_modeText[i].setFont(font);
		m_modeText[i].setPosition(620, 385);
		m_modeText[i].setCharacterSize(150);
		m_modeText[i].setFillColor(sf::Color::Black);
		m_modeText[i].setStyle(sf::Text::Bold);

		// Adding an outline to the text
		m_modeText[i].setOutlineColor(sf::Color(135, 206, 250));
		m_modeText[i].setOutlineThickness(3);

	}
	m_modeText[0].setString("Multiplayer Mode");
	m_modeText[1].setString("Single player Mode");
	m_modeText[2].setString("     Online Mode");

	for (int i = 0; i < m_modeText.size(); i++)
	{
		sf::Text shadow = m_modeText[i];
		shadow.setFillColor(sf::Color(0, 0, 0, 150)); // Semi-transparent black shadow
		shadow.move(5.f, 5.f); // Offset the shadow slightly
		m_shadowText.push_back(shadow);
	}
}
//-------------------------------------------------------------
void GameModeSelection::draw(sf::RenderWindow& window) const {

	window.draw(m_Stage);
	
	sf::Vector2i mouseMove = sf::Mouse::getPosition(window);

	for (int i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i]->draw(window);

		if (m_buttons[i]->contains(sf::Vector2f(float(mouseMove.x),float(mouseMove.y)))) {

			window.draw(m_shadowText[i]);
			window.draw(m_modeText[i]);
		}
	}

	
}
//-------------------------------------------------------------
void GameModeSelection::respond(sf::Vector2f mousePressed) {
	//respond to the buttons pressed
	for (int i = 0; i < m_buttons.size(); i++)
	{
		if (m_buttons[i]->contains(mousePressed)) {
			loadGameMode(i);
			m_buttons[i]->execute();
			return;
		}
	}
}

//-------------------------------------------------------------
void GameModeSelection::loadGameMode(int gameMode)
{

	switch (gameMode)
	{
	case 0:
		m_selectTeamPtr->setNumberOfPlayers(2);
		break;
	case 1:
		m_selectTeamPtr->setNumberOfPlayers(1);
		break;
	default:
		break;
	}
}
//-------------------------------------------------------------
GameModeSelection::~GameModeSelection()
{
}