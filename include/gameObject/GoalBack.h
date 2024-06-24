#pragma once
#include "gameObject/Goal.h"
#include "Factory/StaticFactory.h"



class GoalBack :public Goal
{
public:
	GoalBack(int x, int y, bool needScale);
	~GoalBack();

	virtual void draw(sf::RenderWindow& window) const override;
	virtual sf::Sprite& getSprite()override;

	void setIfGoal(bool ballGetIn);
	bool getIfGoal() const;
	//sf::Vector2f getPotision() const;

private:
	sf::Sprite m_sprite;
	bool m_isGoal;

	static bool m_registeritLeftGoalBack;
	static bool m_registeritRightGoalBack;
};

