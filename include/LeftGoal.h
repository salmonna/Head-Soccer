#pragma once
#include "Resources.h"
#include "Goal.h"

class LeftGoal: public Goal
{
	public:
		LeftGoal();
		virtual ~LeftGoal();
		virtual void draw(sf::RenderWindow& window) override;

	private:
		std::vector<sf::Sprite> m_goalSprite;
};
