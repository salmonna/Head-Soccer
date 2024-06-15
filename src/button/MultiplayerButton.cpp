
#pragma once
#include "button/MultiplayerButton.h"


MultiplayerButton::MultiplayerButton(sf::Texture& texture, Board* boardState) :m_boardState(boardState)
{
	m_multiplayer.setTexture(texture);
	m_multiplayer.setPosition(400, 100);
}

// Method to simulate clicking the button
GameState * MultiplayerButton::click() {
	std::vector<std::string> movingObjectNames{ "RightPlayer", "LeftPlayer", "Ball" };
	std::vector<std::string> staticObjectNames{ "LeftOutsideGoalSide" , "RightOutsideGoalSide" };
	m_boardState->createMovingObjects(movingObjectNames);
	m_boardState->createStaticObjects(staticObjectNames);
	return m_boardState;
}

// Method to display button information
void MultiplayerButton::draw(sf::RenderWindow& window) const {
	window.draw(m_multiplayer);
}

// Method to check button position
bool MultiplayerButton::contains(sf::Vector2f position) const {
	sf::Vector2f newPos = m_multiplayer.getTransform().getInverse().transformPoint(position);
	return m_multiplayer.getLocalBounds().contains(newPos);
}