#pragma once
#include <vector>
#include "Resources.h"

class Goal
{
	public:
		Goal();
		~Goal();
		void draw(sf::RenderWindow & window);

	private:

		std::vector<sf::Sprite> m_goalSprite;
};
