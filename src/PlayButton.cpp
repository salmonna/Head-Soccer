
#pragma once
#include "PlayButton.h"


PlayButton::PlayButton(sf::Texture& texture)
{
	m_play.setTexture(texture);
	m_play.setPosition(100, 100);

}

// Method to simulate clicking the button
bool PlayButton::click() {
	return false;
}

// Method to display button information
void PlayButton::draw(sf::RenderWindow& window) const {
	window.draw(m_play);
}

// Method to check button position
bool PlayButton::contains(sf::Vector2f position) const {
	return m_play.getGlobalBounds().contains(position);
}