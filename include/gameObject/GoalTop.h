#pragma once
#include "gameObject/Goal.h"
#include "Factory/StaticFactory.h"


class GoalTop : public Goal
{
public:
	GoalTop(int x, int y, bool needScale);
	~GoalTop();

	virtual void draw(sf::RenderWindow& window)const override;
	virtual sf::Sprite& getSprite()override;

private:

	sf::Sprite m_sprite;

	static bool m_registeritLeftGoalTop;
	static bool m_registeritRightGoalTop;
};

