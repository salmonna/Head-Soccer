
#pragma once
#include "button/PlayerButton.h"

PlayerButton::PlayerButton(sf::Texture& texture, Board* boardState, SelectTeam* selectTeam) :m_boardState(boardState),m_selectTeam(selectTeam)
{
	m_player.setTexture(texture);
	m_player.setPosition(800, 100);
}

// Method to simulate clicking the button
GameState * PlayerButton::click() {
	std::vector<std::string> movingObjectNames{ "RightPlayer", "ComputerPlayer", "Ball" };
	std::vector<std::string> staticObjectNames{ "LeftOutsideGoalSide" , "RightOutsideGoalSide" };
	m_boardState->createMovingObjects(movingObjectNames);
	m_boardState->createStaticObjects(staticObjectNames);
	m_selectTeam->setNumberOfPlayers(1);
	return m_selectTeam;
}

// Method to display button information
void PlayerButton::draw(sf::RenderWindow& window) const {
	window.draw(m_player);
}

// Method to check button position
bool PlayerButton::contains(sf::Vector2f position) const {
	return m_player.getGlobalBounds().contains(position);
}