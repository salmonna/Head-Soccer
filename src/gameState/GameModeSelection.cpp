
#include "gameState/GameModeSelection.h"
#include "Resources.h"
#include "Command/SwichScreen.h"
#include "Command/Undo.h"
#include "Command/Command.h"

GameModeSelection::GameModeSelection(Controller* controller, Board* boardState, Menu* menu, SelectTeam* selectTeam):m_boardPtr(boardState), m_selectTeamPtr(selectTeam)
, m_prevState(menu)
{
	std::vector<sf::Texture>& texture = Resources::getInstance().getGameModeTexture();
	m_Stage.setTexture(texture[0]);
	m_buttons.push_back(std::make_unique<Button>(std::move(std::make_unique<SwichScreen>(selectTeam, controller)), texture[1], sf::Vector2f(400.f, 100.f))); //Button 1
	m_buttons.push_back(std::make_unique<Button>(std::move(std::make_unique<SwichScreen>(selectTeam, controller)), texture[2], sf::Vector2f(800.f, 100.f))); //Button 2
	m_buttons.push_back(std::make_unique<Button>(std::move(std::make_unique<SwichScreen>(selectTeam, controller)), texture[3], sf::Vector2f(1200.f, 100.f))); //Button 3
	m_buttons.push_back(std::make_unique<Button>(std::move(std::make_unique<Undo>(controller)), Resources::getInstance().getMenuTexture()[7], sf::Vector2f(0, 0))); //Button 4



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
	std::vector<std::string> movingObjectNames{ "RightPlayer", "LeftPlayer", "Ball" };
	std::vector<std::string> staticObjectNames{ "LeftOutsideGoalSide" , "RightOutsideGoalSide" };
	switch (gameMode)
	{
	case 0:

		m_selectTeamPtr->setNumberOfPlayers(2);
		break;
	case 1:
		movingObjectNames[1] = "ComputerPlayer";
		m_selectTeamPtr->setNumberOfPlayers(1);
		break;
	case 2:
		break;
	default:
		break;
	}
	m_boardPtr->createMovingObjects(movingObjectNames);
	m_boardPtr->createStaticObjects(staticObjectNames);

}


GameState * GameModeSelection::prevState()
{
	return m_prevState;
}

GameModeSelection::~GameModeSelection()
{
}