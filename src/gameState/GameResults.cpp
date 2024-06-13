#include "gameState/GameResults.h"
#include "Resources.h"

//gameResults constactor
GameResults::GameResults()
{
	std::vector<sf::Texture>& texturs = Resources::getInstance().getGameModeTexture();

	

}

//respond function check if there is a click on the exit button
void GameResults::respond(sf::Vector2f mouseClick)
{

}

//draw function
void GameResults::draw(sf::RenderWindow& window) const
{

}

// check if game result is open
bool GameResults::isOpen()
{
	return m_gameResultsOpen;
}

