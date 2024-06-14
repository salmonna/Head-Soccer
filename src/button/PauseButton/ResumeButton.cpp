#pragma once
#include "button/pauseButton/ResumeButton.h"
#include "Resources.h"


ResumeButton::ResumeButton(Board * boardState) :m_boardState(boardState)
{
	sf::Texture& texture = Resources::getInstance().getMenuTexture()[0];
	m_sprite.setTexture(texture);
	m_sprite.setPosition(1800/2- m_sprite.getPosition().x,  1013 / 2);
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
	return m_sprite.getGlobalBounds().contains(position);
}