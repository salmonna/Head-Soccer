
#include "gameState/GameModeSelection.h"
#include "Resources.h"
#include "Command/SwichScreen.h"
#include "Command/Command.h"

GameModeSelection::GameModeSelection(Controller* controller, Board* boardState, SelectTeam* selectTeam):m_boardPtr(boardState), m_selectTeamPtr(selectTeam)
{
	std::vector<sf::Texture>& texture = Resources::getInstance().getGameModeTexture();
	m_Stage.setTexture(texture[0]);
	m_buttons.push_back(std::make_unique<Button>(std::move(std::make_unique<SwichScreen>(selectTeam, controller)), texture[1], sf::Vector2f(400.f, 100.f))); //Button 1
	m_buttons.push_back(std::make_unique<Button>(std::move(std::make_unique<SwichScreen>(selectTeam, controller)), texture[2], sf::Vector2f(800.f, 100.f))); //Button 2
	m_buttons.push_back(std::make_unique<Button>(std::move(std::make_unique<SwichScreen>(selectTeam, controller)), texture[3], sf::Vector2f(1200.f, 100.f))); //Button 3


}

void GameModeSelection::draw(sf::RenderWindow& window) const {
	window.draw(m_Stage);
	for (int i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i]->draw(window);
	}
}

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


void GameModeSelection::loadGameMode(int gameMode)
{
	if (gameMode == 0)
	{
		m_selectTeamPtr->setNumberOfPlayers(2);
	}
	else if (gameMode == 1)
	{
		m_selectTeamPtr->setNumberOfPlayers(1);
	}
}


GameModeSelection::~GameModeSelection()
{
}