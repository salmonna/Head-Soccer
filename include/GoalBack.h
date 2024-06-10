#pragma once

#include "gameObject/Goal.h"

class GoalBack :public Goal
{
public:
	GoalBack(int x, int y, bool needScale);
	~GoalBack();

	virtual void draw(sf::RenderWindow& window) override;
	virtual sf::Sprite& getSprite()override;

private:
	sf::Sprite m_sprite;

};

