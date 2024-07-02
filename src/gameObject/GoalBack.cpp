#include "gameObject/GoalBack.h"
#include "Box2d.h"

GoalBack::GoalBack(int x, int y, bool needScale):m_side(needScale)
{

	m_sprite.setTexture(Resources::getInstance().getGoalTexture(1));
	m_sprite.setPosition(x, y);
	m_sprite.scale(0.6f, 0.6f);
	

	if (m_side) {
		m_body = Box2d::getInstance().createGoalBack(sf::Vector2f(x - 60,y + 110));
		m_sprite.scale(-1, 1);
	}
	else
	{
		m_body = Box2d::getInstance().createGoalBack(sf::Vector2f(x + 60, y + 110));
	}
}


bool GoalBack::m_registeritLeftGoalBack = StaticFactory::registeritStatic("LeftGoalBack",
	[]() -> std::shared_ptr<StaticObject> { return std::make_shared<GoalBack>(-15, 590, false); });


bool GoalBack::m_registeritRightGoalBack = StaticFactory::registeritStatic("RightGoalBack",
	[]() -> std::shared_ptr<StaticObject> { return std::make_shared<GoalBack>(1805, 590, true); });


void GoalBack::draw(sf::RenderWindow& window)const {

	window.draw(m_sprite);
}

b2Body* GoalBack::getBody() {
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