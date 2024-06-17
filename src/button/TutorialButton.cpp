#pragma once
#include "button/TutorialButton.h"
#include "Resources.h"
#include <string>
#include <SFML/Graphics.hpp>

TutorialButton::TutorialButton(sf::Texture& texture):m_buttonPressed(false)
{
	m_tutorial.setTexture(texture);
	m_tutorial.setPosition(100, 400);
	m_tutorialText.setFont(Resources::getInstance().getFont());

	m_tutorialText.setString(getText());
	m_tutorialText.setCharacterSize(60);
	m_tutorialText.setPosition(400, 100);
}

// Method to simulate clicking the button
GameState * TutorialButton::click(){
	(m_buttonPressed) ? m_buttonPressed = false : m_buttonPressed = true;
	return NULL;
}

// Method to display button information
void TutorialButton::draw(sf::RenderWindow& window) const {
	window.draw(m_tutorial);
	if (m_buttonPressed)
	{
		window.draw(m_tutorialText);
	}
}

// Method to check button position
bool TutorialButton::contains(sf::Vector2f position) const {
	return m_tutorial.getGlobalBounds().contains(position);
}


std::string TutorialButton::getText() const {
	std::string text;

	text = "Controls: Use the left/right arrows to move, jump button to jump, and kick button to kick or charge a power shot.\n "
		"Objective: Score more goals than your opponent within the time limit.\n "
		"Strategy: Position yourself between the ball and your goal, use power shots strategically.";

	return text;
}
