#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class Goal
{
	public:
		Goal();
		~Goal();
		void draw(sf::RenderWindow & window);

	private:

		std::vector<sf::Sprite> m_goalSprite;
};
