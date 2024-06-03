#include "LeftGoal.h"


//--------- C-tor --------------
LeftGoal::LeftGoal()
{

	std::vector<sf::Texture>& goalTexture = Resources::getInstance().getGoalTexture();

	auto otherSideGoal = sf::Sprite();

	for (size_t i = 0; i < goalTexture.size(); i++)
	{
		auto sprite = sf::Sprite(goalTexture[i]);
		sprite.scale(0.6f, 0.6f);
		m_goalSprite.push_back(sprite);

		//get other side of the goal
		if (i == 0) {
			otherSideGoal = sprite;
		}
	}
	//set the other side of the goal
	m_goalSprite.push_back(otherSideGoal);

	//set the position of the left goal
	m_goalSprite[0].setPosition(32, 580);
	m_goalSprite[1].setPosition(-15, 590);
	m_goalSprite[2].setPosition(40, 580);
	m_goalSprite[3].setPosition(-20, 625);
}

//---------------- draw the goal --------------------
void LeftGoal::draw(sf::RenderWindow& window) {

	for (int i = 0; i < m_goalSprite.size(); i++)
	{
		window.draw(m_goalSprite[i]);
	}
}

//--------- D-tor --------------
LeftGoal::~LeftGoal()
{
}