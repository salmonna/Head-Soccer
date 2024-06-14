#pragma once
#include "button/pauseButton/ExitButton.h"
#include "Resources.h"


ExitButton::ExitButton(Menu* menuState) :m_menuState(menuState)
{
	sf::Texture& texture = Resources::getInstance().getMenuTexture()[1];
	m_sprite.setTexture(texture);
	m_sprite.setPosition(1800 / 2 - m_sprite.getPosition().x, 1013 / 2+200);
}

// Method to simulate clicking the button
GameState* ExitButton::click() {
	return m_menuState;
}

// Method to display button information
void ExitButton::draw(sf::RenderWindow& window) const {
	window.draw(m_sprite);
}

// Method to check button position
bool ExitButton::contains(sf::Vector2f position) const {
	return m_sprite.getGlobalBounds().contains(position);
}