#pragma once
#include "button/pauseButton/ResumeButton.h"
#include "Resources.h"


ResumeButton::ResumeButton(Board * boardState) :m_boardState(boardState)
{
	sf::Texture& texture = Resources::getInstance().getPauseTexture()[1];
	m_sprite.setTexture(texture);
	m_sprite.setPosition(1800/2- m_sprite.getLocalBounds().width/2,  1013 / 2- m_sprite.getLocalBounds().height/2-200);
}

// Method to simulate clicking the button
GameState* ResumeButton::click() {
	return m_boardState;
}

// Method to display button information
void ResumeButton::draw(sf::RenderWindow& window) const {
	window.draw(m_sprite);
}

// Method to check button position
bool ResumeButton::contains(sf::Vector2f position) const {
	sf::Vector2f newPos = m_sprite.getTransform().getInverse().transformPoint(position);
	return m_sprite.getLocalBounds().contains(newPos);
}