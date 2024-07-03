#include "gameObject/GoalTop.h"

GoalTop::GoalTop(float x, float y, bool needScale)
{
	m_sprite.setTexture(Resources::getInstance().getGoalTexture(2));
	m_sprite.setPosition(x, y);
	m_sprite.scale(0.6f, 0.6f);

	if (needScale) {

		m_sprite.scale(-1.f, 1.f);
	}
}


bool GoalTop::m_registeritLeftGoalTop = StaticFactory::registeritStatic("LeftGoalTop",
	[]() -> std::shared_ptr<StaticObject> { return std::make_shared<GoalTop>(40.f, 580.f, false); });


bool GoalTop::m_registeritRightGoalTop = StaticFactory::registeritStatic("RightGoalTop",
	[]() -> std::shared_ptr<StaticObject> { return std::make_shared<GoalTop>(1750.f, 580.f, true); });

void GoalTop::draw(sf::RenderWindow& window)const {

	window.draw(m_sprite);
}

sf::Sprite& GoalTop::getSprite() {

	return m_sprite;
}

GoalTop::~GoalTop()
{
}