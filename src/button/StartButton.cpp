#include "button/StartButton.h"
#include "Resources.h"

StartButton::StartButton(Board* boardState) : m_boardState(boardState)
{
	m_start.setTexture(Resources::getInstance().getSelectTeam()[0]);
	m_start.setPosition(550,790);
}


GameState* StartButton::click() {

	return m_boardState;
}


void StartButton::draw(sf::RenderWindow& window) const {

	window.draw(m_start);
}


bool StartButton::contains(sf::Vector2f position) const{

	return m_start.getGlobalBounds().contains(position);
}

StartButton::~StartButton()
{
}