#pragma once

#include "Goal.h"

class GoalBack :public Goal
{
public:
	GoalBack(int x, int y, bool needScale);
	~GoalBack();

	virtual void draw(sf::RenderWindow& window) override;
	virtual sf::Sprite& getSprite()override;

	void setIfGoal(bool ballGetIn);
	bool getIfGoal() const;
	//sf::Vector2f getPotision() const;

private:
	sf::Sprite m_sprite;
	bool m_isGoal;
};

