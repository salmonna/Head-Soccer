
#pragma once
#include "button/OnlineButton.h"

OnlineButton::OnlineButton(sf::Texture& texture, Board* boardState) :m_boardState(boardState)
{
	m_online.setTexture(texture);
	m_online.setPosition(1200, 100);
}

// Method to simulate clicking the button
GameState* OnlineButton::click() {
	return m_boardState;
}

// Method to display button information
void OnlineButton::draw(sf::RenderWindow& window) const {
	window.draw(m_online);
}

// Method to check button position
bool OnlineButton::contains(sf::Vector2f position) const {
	sf::Vector2f newPos = m_online.getTransform().getInverse().transformPoint(position);
	return m_online.getLocalBounds().contains(newPos);
}