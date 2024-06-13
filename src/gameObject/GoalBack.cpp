#include "gameObject/GoalBack.h"

GoalBack::GoalBack(int x, int y, bool needScale):m_isGoal(false)
{

	m_sprite.setTexture(Resources::getInstance().getGoalTexture(1));
	m_sprite.setPosition(x, y);
	m_sprite.scale(0.6f, 0.6f);

	if (needScale) {

		m_sprite.scale(-1, 1);
	}
}


bool GoalBack::m_registeritLeftGoalBack = StaticFactory::registeritStatic("LeftGoalBack",
	[]() -> std::shared_ptr<StaticObject> { return std::make_shared<GoalBack>(-15, 590, false); });


bool GoalBack::m_registeritRightGoalBack = StaticFactory::registeritStatic("RightGoalBack",
	[]() -> std::shared_ptr<StaticObject> { return std::make_shared<GoalBack>(1805, 590, true); });


void GoalBack::draw(sf::RenderWindow& window)const {

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

GoalBack::~GoalBack()
{
}