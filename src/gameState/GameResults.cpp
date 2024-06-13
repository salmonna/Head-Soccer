#include "gameState/GameResults.h"
#include "Resources.h"

//gameResults constactor
GameResults::GameResults():m_sprite(Resources::getInstance().getGameModeTexture()[0])
{

}

//respond function check if there is a click on the exit button
void GameResults::respond(sf::Vector2f mouseClick)
{

}

//draw function
void GameResults::draw(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}


GameState* GameResults::handleEvents() 
{
	return NULL;
}