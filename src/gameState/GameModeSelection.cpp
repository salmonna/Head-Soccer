
#include "gameState/GameModeSelection.h"
#include "Resources.h"
#include "button/MultiplayerButton.h"
#include "button/PlayerButton.h"
#include "button/OnlineButton.h"

GameModeSelection::GameModeSelection(Board* boardState, SelectTeam* selectTeam):m_gameState(NULL)
{
	std::vector<sf::Texture>& texturs = Resources::getInstance().getGameModeTexture();
	m_Stage.setTexture(texturs[0]);
	m_buttons.push_back(std::make_unique<MultiplayerButton>(texturs[1], boardState, selectTeam));
	m_buttons.push_back(std::make_unique<PlayerButton>(texturs[2], boardState, selectTeam));
	m_buttons.push_back(std::make_unique<OnlineButton>(texturs[3], selectTeam));
}

void GameModeSelection::draw(sf::RenderWindow& window) const {
	window.draw(m_Stage);
	for (int i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i]->draw(window);
	}
}

void GameModeSelection::respond(sf::Vector2f mousePressed) {
	for (int i = 0; i < m_buttons.size(); i++)
	{
		if (m_buttons[i]->contains(mousePressed))
		{
			m_gameState = m_buttons[i]->click();
			break;
		}
	}
}

GameState* GameModeSelection::handleEvents() {
	GameState* gameState = m_gameState;
	m_gameState = NULL;
	return gameState;
}

GameModeSelection::~GameModeSelection()
{
}