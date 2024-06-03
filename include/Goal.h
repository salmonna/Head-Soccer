#pragma once
#include <vector>
#include "Resources.h"

class Goal
{
	public:
		Goal();
		virtual ~Goal();
		virtual void draw(sf::RenderWindow & window) = 0;

	private:

		std::vector<sf::Sprite> m_goalSprite;
};
