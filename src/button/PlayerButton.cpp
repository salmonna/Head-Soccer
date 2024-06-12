
#pragma once
#include "button/PlayerButton.h"

PlayerButton::PlayerButton(sf::Texture& texture, Board* boardState) :m_boardState(boardState)
{
	m_player.setTexture(texture);
	m_player.setPosition(900, 100);
}

// Method to simulate clicking the button
GameState * PlayerButton::click() {
	return m_boardState;
}

// Method to display button information
void PlayerButton::draw(sf::RenderWindow& window) const {
	window.draw(m_player);
}

// Method to check button position
bool PlayerButton::contains(sf::Vector2f position) const {
	return m_player.getGlobalBounds().contains(position);
}