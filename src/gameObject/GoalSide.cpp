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


bool GoalSide::m_registeritLeftInsideGoalSide = StaticFactory::registeritStatic("LeftInsideGoalSide",
	[]() -> std::shared_ptr<StaticObject> { return std::make_shared<GoalSide>(32, 580, false); });


bool GoalSide::m_registeritRightInsideGoalSide = StaticFactory::registeritStatic("RightInsideGoalSide",
	[]() -> std::shared_ptr<StaticObject> { return std::make_shared<GoalSide>(1755, 580, true); });


bool GoalSide::m_registeritLeftOutsideGoalSide = StaticFactory::registeritStatic("LeftOutsideGoalSide",
	[]() -> std::shared_ptr<StaticObject> { return std::make_shared<GoalSide>(-20, 625, false); });


bool GoalSide::m_registeriiRightOutsideGoalSide = StaticFactory::registeritStatic("RightOutsideGoalSide",
	[]() -> std::shared_ptr<StaticObject> { return std::make_shared<GoalSide>(1810, 625, true); });


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