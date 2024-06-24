#pragma once
#include "button/QuitButton.h"

QuitButton::QuitButton(sf::Texture& texture, sf::RenderWindow * window):m_window(window)
{
	m_quit.setTexture(texture);
	m_quit.setPosition(100, 200);

}


// Method to simulate clicking the button
GameState * QuitButton::click() {
	m_window->close();
	return NULL;
}

// Method to display button information
void QuitButton::draw(sf::RenderWindow& window) const {
	window.draw(m_quit);
}

// Method to check button position
bool QuitButton::contains(sf::Vector2f position) const {
	return m_quit.getGlobalBounds().contains(position);
}
