#pragma once
#include <vector>
#include "Resources.h"

class RightGoal
{
	public:
		RightGoal();
		~RightGoal();

		void draw(sf::RenderWindow &  window);

	private:
		std::vector<sf::Sprite> m_rightGoal;
};
