#include "gameObject/GoalSide.h"

GoalSide::GoalSide(int x , int y , bool needScale)
{
	m_sprite.setTexture(Resources::getInstance().getGoalTexture(0));
	m_sprite.setPosition(x, y);
	m_sprite.scale(0.6f,0.6f);

	if (needScale) {

		m_sprite.scale(-1,1);
	}
}


void GoalSide::draw(sf::RenderWindow& window) {

	window.draw(m_sprite);
}

//---------------------------------------
sf::Sprite& GoalSide::getSprite() {

	return m_sprite;
}

GoalSide::~GoalSide()
{
}