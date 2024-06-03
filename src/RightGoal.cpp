#include "RightGoal.h"

//--------- C-tor --------------
RightGoal::RightGoal()
{

	std::vector<sf::Texture>& m_rightGoalTexture = Resources::getInstance().getGoalTexture();

	auto otherSideGoal = sf::Sprite();

	for (size_t i = 0; i < m_rightGoalTexture.size(); i++)
	{
		auto sprite = sf::Sprite(m_rightGoalTexture[i]);
		sprite.scale(-1, 1);
		sprite.scale(0.6f, 0.6f);
		
		m_rightGoal.push_back(sprite);

		if (i == 0) {
			otherSideGoal = sprite;
		}
	}
	m_rightGoal.push_back(otherSideGoal);
	m_rightGoal[0].setPosition(1755,580);
}

//---------------- draw the goal --------------------
void RightGoal::draw(sf::RenderWindow& window) {

	
	window.draw(m_rightGoal[0]);
}

//--------- D-tor --------------
RightGoal::~RightGoal()
{
}