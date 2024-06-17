
#pragma once
#include "button/OnlineButton.h"

OnlineButton::OnlineButton(sf::Texture& texture, SelectTeam* selectTeam) :m_selectTeam(selectTeam)
{
	m_online.setTexture(texture);
	m_online.setPosition(1200, 100);
}

// Method to simulate clicking the button
GameState* OnlineButton::click() {

	m_selectTeam->setNumberOfPlayers(1);
	return m_selectTeam;
}

// Method to display button information
void OnlineButton::draw(sf::RenderWindow& window) const {
	window.draw(m_online);
}

// Method to check button position
bool OnlineButton::contains(sf::Vector2f position) const {
	return m_online.getGlobalBounds().contains(position);
}