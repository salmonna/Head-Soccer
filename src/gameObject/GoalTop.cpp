#include "gameObject/GoalTop.h"

GoalTop::GoalTop(int x, int y, bool needScale)
{
	m_sprite.setTexture(Resources::getInstance().getGoalTexture(2));
	m_sprite.setPosition(x, y);
	m_sprite.scale(0.6f, 0.6f);

	if (needScale) {

		m_sprite.scale(-1, 1);
	}
}


void GoalTop::draw(sf::RenderWindow& window) {

	window.draw(m_sprite);
}

sf::Sprite& GoalTop::getSprite() {

	return m_sprite;
}

GoalTop::~GoalTop()
{
}