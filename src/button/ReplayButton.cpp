
#include "button/ReplayButton.h"

ReplayButton::ReplayButton(sf::Texture& texture, GameModeSelection* menuState):m_menuState(menuState)
{
	m_replayButton.setTexture(texture);
	m_replayButton.setPosition(100, 200);

}

// Method to simulate clicking the button
GameState* ReplayButton::click() {
	return m_menuState;
}

// Method to display button information
void ReplayButton::draw(sf::RenderWindow& window) const {
	window.draw(m_replayButton);
}

// Method to check button position
bool ReplayButton::contains(sf::Vector2f position) const {
	return m_replayButton.getGlobalBounds().contains(position);
}
