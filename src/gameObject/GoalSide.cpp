#include "gameObject/GoalSide.h"

GoalSide::GoalSide(float x , float y , bool needScale)
{
	m_sprite.setTexture(Resources::getInstance().getGoalTexture(0));
	m_sprite.setPosition(x, y);
	m_sprite.scale(0.6f,0.6f);

	if (needScale) {

		m_sprite.scale(-1.f,1.f);
	}
}


bool GoalSide::m_registeritLeftInsideGoalSide = StaticFactory::registeritStatic("LeftInsideGoalSide",
	[]() -> std::shared_ptr<StaticObject> { return std::make_shared<GoalSide>(32.f, 580.f, false); });


bool GoalSide::m_registeritRightInsideGoalSide = StaticFactory::registeritStatic("RightInsideGoalSide",
	[]() -> std::shared_ptr<StaticObject> { return std::make_shared<GoalSide>(1755.f, 580.f, true); });


bool GoalSide::m_registeritLeftOutsideGoalSide = StaticFactory::registeritStatic("LeftOutsideGoalSide",
	[]() -> std::shared_ptr<StaticObject> { return std::make_shared<GoalSide>(-20.f, 625.f, false); });


bool GoalSide::m_registeriiRightOutsideGoalSide = StaticFactory::registeritStatic("RightOutsideGoalSide",
	[]() -> std::shared_ptr<StaticObject> { return std::make_shared<GoalSide>(1810.f, 625.f, true); });


void GoalSide::draw(sf::RenderWindow& window)const {

	window.draw(m_sprite);
}

//---------------------------------------
sf::Sprite& GoalSide::getSprite() {

	return m_sprite;
}

GoalSide::~GoalSide()
{
}