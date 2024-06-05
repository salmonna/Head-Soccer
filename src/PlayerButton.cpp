
#pragma once
#include "PlayerButton.h"


PlayerButton::PlayerButton(sf::Texture& texture)
{
	m_player.setTexture(texture);
	m_player.setPosition(900, 100);
}

// Method to simulate clicking the button
bool PlayerButton::click() {
	return false;
}

// Method to display button information
void PlayerButton::draw(sf::RenderWindow& window) const {
	window.draw(m_player);
}

// Method to check button position
bool PlayerButton::contains(sf::Vector2f position) const {
	return m_player.getGlobalBounds().contains(position);
}