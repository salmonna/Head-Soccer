#include "GoalBack.h"

GoalBack::GoalBack(int x, int y, bool needScale)
{

	m_sprite.setTexture(Resources::getInstance().getGoalTexture(1));
	m_sprite.setPosition(x, y);
	m_sprite.scale(0.6f, 0.6f);

	if (needScale) {

		m_sprite.scale(-1, 1);
	}
}

void GoalBack::draw(sf::RenderWindow& window) {

	window.draw(m_sprite);
}

sf::Sprite& GoalBack::getSprite() {

	return m_sprite;
}

GoalBack::~GoalBack()
{
}