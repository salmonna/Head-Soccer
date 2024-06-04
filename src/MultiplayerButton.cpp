
#pragma once
#include "MultiplayerButton.h"


MultiplayerButton::MultiplayerButton(sf::Texture& texture)
{
	m_multiplayer.setTexture(texture);
	m_multiplayer.setPosition(500, 100);
}

// Method to simulate clicking the button
bool MultiplayerButton::click() {
	return false;
}

// Method to display button information
void MultiplayerButton::draw(sf::RenderWindow& window) const {
	window.draw(m_multiplayer);
}

// Method to check button position
bool MultiplayerButton::contains(sf::Vector2f position) const {
	return m_multiplayer.getGlobalBounds().contains(position);
}