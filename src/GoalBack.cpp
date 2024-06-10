#include "GoalBack.h"

GoalBack::GoalBack(int x, int y, bool needScale):m_isGoal(false)
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


void GoalBack::setIfGoal(bool ballGetIn) {
	
	m_isGoal = ballGetIn;
}

bool GoalBack::getIfGoal() const {
	return m_isGoal;
}
//sf::Vector2f GoalBack::getPotision() const {
//
//	return m_sprite.getPosition();
//}
GoalBack::~GoalBack()
{
}