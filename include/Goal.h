#pragma once
#include "Resources.h"

class Goal 
{
public:
	Goal();
	~Goal();
	void draw(sf::RenderWindow& window);
	void setRightGoal();

private:
	std::vector<sf::Sprite> m_goalSprite;
};
