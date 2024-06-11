#pragma once

#include "gameObject/Goal.h"

class GoalBack :public Goal
{
public:
	GoalBack(int x, int y, bool needScale);
	~GoalBack();

	virtual void draw(sf::RenderWindow& window) const override;
	virtual sf::Sprite& getSprite()override;

	void setIfGoal(bool ballGetIn);
	bool getIfGoal() const;
private:
	sf::Sprite m_sprite;
	bool m_isGoal;
};

