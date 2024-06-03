#pragma once
#include <vector>
#include "Resources.h"
#include "Goal.h"

class RightGoal :public Goal
{
	public:
		RightGoal();
		virtual ~RightGoal();

		virtual void draw(sf::RenderWindow &  window) override;

	private:
		std::vector<sf::Sprite> m_rightGoal;
};
