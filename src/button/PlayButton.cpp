
#pragma once
#include "button/PlayButton.h"
#include "memory.h"

PlayButton::PlayButton(sf::Texture& texturs, Board* boardState):m_boardState(boardState),
m_playPressed(false)
{
	m_play.setTexture(texturs);
	m_play.setPosition(100, 100);

}

// Method to simulate clicking the button
GameState * PlayButton::click() {
	return m_boardState;
}

// Method to display button information
void PlayButton::draw(sf::RenderWindow& window) const {
	window.draw(m_play);
}

// Method to check button position
bool PlayButton::contains(sf::Vector2f position) const {
	return m_play.getGlobalBounds().contains(position);
}