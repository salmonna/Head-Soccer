#include "Goal.h"
#include "Resources.h"


//--------- C-tor --------------
Goal::Goal()
{

	std::vector<sf::Texture>& goalTexture = Resources::getInstance().getGoalTexture();

	auto otherSideGoal = sf::Sprite();

	for (size_t i = 0; i < goalTexture.size(); i++)
	{
		auto sprite= sf::Sprite(goalTexture[i]);
		sprite.scale(0.6,0.6);
		m_goalSprite.push_back(sprite);

		//get other side of the goal
		if (i == 0) {
			otherSideGoal = sprite;
		}
	}
	//set the other side of the goal
	m_goalSprite.push_back(otherSideGoal);
	m_goalSprite[0].setPosition(32,580);

	//need to change position to goal sides
	
}


void Goal::draw(sf::RenderWindow& window) {

	window.draw(m_goalSprite[0]);
}

//--------- D-tor --------------
Goal::~Goal()
{
}