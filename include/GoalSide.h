#pragma once

#include "Goal.h"

class GoalSide : public Goal
{
	public:
		GoalSide(int x, int y, bool needScale);
		~GoalSide();

		virtual void draw(sf::RenderWindow& window) override;
		virtual sf::Sprite& getSprite()override;

	private:
		sf::Sprite m_sprite;

};

