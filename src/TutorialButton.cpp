#pragma once
#include "TutorialButton.h"

TutorialButton::TutorialButton(sf::Texture& texture)
{
	m_tutorial.setTexture(texture);
	m_tutorial.setPosition(100, 400);
}


// Method to simulate clicking the button
bool TutorialButton::click() const {
	return true;
}

// Method to display button information
void TutorialButton::draw(sf::RenderWindow& window) const {
	window.draw(m_tutorial);
}

// Method to check button position
bool TutorialButton::contains(sf::Vector2f position) const {
	return m_tutorial.getGlobalBounds().contains(position);
}
