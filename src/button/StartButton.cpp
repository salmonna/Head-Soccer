#include "button/StartButton.h"
#include "Resources.h"

StartButton::StartButton(Board* boardState, SelectTeam* selectTeam) : m_boardState(boardState), m_selectTeam(selectTeam)
{
	m_start.setTexture(Resources::getInstance().getSelectTeam()[0]);
	m_start.setPosition(520,690);
}


GameState* StartButton::click() {
	//m_selectTeam->reset();
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