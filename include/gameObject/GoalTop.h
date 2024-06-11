#pragma once

#include "gameObject/Goal.h"

class GoalTop : public Goal
{
public:
	GoalTop(int x, int y, bool needScale);
	~GoalTop();

	virtual void draw(sf::RenderWindow& window)const override;
	virtual sf::Sprite& getSprite()override;
private:

	sf::Sprite m_sprite;
};

