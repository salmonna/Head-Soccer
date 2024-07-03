#include "gameObject/GoalBack.h"
#include "Box2d.h"

GoalBack::GoalBack(float x, float y, bool needScale):m_side(needScale)
{
	
	m_sprite.setTexture(Resources::getInstance().getGoalTexture(1));
	m_sprite.setPosition(x,y);
	m_sprite.scale(0.6f, 0.6f);
	

	if (m_side) {
		m_body = Box2d::getInstance().createGoalBack(sf::Vector2f(x - 60.f,y + 110.f));
		m_sprite.scale(-1, 1);
	}
	else
	{
		m_body = Box2d::getInstance().createGoalBack(sf::Vector2f(x + 60.f, y + 110.f));
	}
}


bool GoalBack::m_registeritLeftGoalBack = StaticFactory::registeritStatic("LeftGoalBack",
	[]() -> std::shared_ptr<StaticObject> { return std::make_shared<GoalBack>(-15.f, 590.f, false); });


bool GoalBack::m_registeritRightGoalBack = StaticFactory::registeritStatic("RightGoalBack",
	[]() -> std::shared_ptr<StaticObject> { return std::make_shared<GoalBack>(1805.f, 590.f, true); });


void GoalBack::draw(sf::RenderWindow& window)const {

	window.draw(m_sprite);
}

b2Body* GoalBack::getBody()const {
	return m_body;
}

sf::Sprite& GoalBack::getSprite() {

	return m_sprite;
}

bool GoalBack::getGoalSide() const {
	return m_side;
}

GoalBack::~GoalBack()
{
}