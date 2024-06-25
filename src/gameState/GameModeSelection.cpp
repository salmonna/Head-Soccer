
#include "gameState/GameModeSelection.h"
#include "Resources.h"
#include "Command/SwichScreen.h"
#include "Command/Command.h"

GameModeSelection::GameModeSelection(Controller* controller, Board* boardState, SelectTeam* selectTeam):m_boardPtr(boardState), m_selectTeamPtr(selectTeam)
{
	std::vector<sf::Texture>& texture = Resources::getInstance().getGameModeTexture();
	m_Stage.setTexture(texture[0]);
	//m_buttons.push_back(std::make_unique<MultiplayerButton>(texturs[1], boardState, selectTeam));
	//m_buttons.push_back(std::make_unique<PlayerButton>(texturs[2], boardState, selectTeam));
	//m_buttons.push_back(std::make_unique<OnlineButton>(texturs[3], selectTeam));

	m_buttons.push_back(std::make_unique<Button>(std::move(std::make_unique<SwichScreen>(selectTeam, controller)), texture[1], sf::Vector2f(100.f, 100.f))); //playButton

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
		m_boardPtr->createMovingObjects(movingObjectNames);
		m_boardPtr->createStaticObjects(staticObjectNames);
		m_selectTeamPtr->setNumberOfPlayers(2);
		break;

	case 1:

		break;

	case 2:

		break;

	default:
		break;
	}
}


GameModeSelection::~GameModeSelection()
{
}