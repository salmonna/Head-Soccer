#include "Goal.h"
#include <iostream>

//--------- C-tor --------------
Goal::Goal()
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
void Goal::draw(sf::RenderWindow& window) {

	for (int i = 0; i < m_goalSprite.size(); i++)
	{
		window.draw(m_goalSprite[i]);
	}

	//std::cout << m_goalSprite[2].getGlobalBounds().getPosition().x << "\n";
	//std::cout << m_goalSprite[2].getGlobalBounds().getPosition().y << "\n";

	//std::cout << m_goalSprite[2].getGlobalBounds().getPosition().x + m_goalSprite[2].getGlobalBounds().width << "\n";
	//std::cout << m_goalSprite[2].getGlobalBounds().getPosition().y + m_goalSprite[2].getGlobalBounds().height << "\n";

}

//-----------set Right Goal -------------------------
void Goal::setRightGoal() {

	//change direction of the goal to right by scale
	for (size_t i = 0; i < m_goalSprite.size(); i++)
	{
		m_goalSprite[i].scale(-1, 1);
		
	}

	//set position of the right goal 
	m_goalSprite[0].setPosition(1755, 580);
	m_goalSprite[1].setPosition(1805, 590);
	m_goalSprite[2].setPosition(1750, 580);
	m_goalSprite[3].setPosition(1810, 625);

}

sf::Sprite& Goal::getSprite() {

	return m_goalSprite[1];
}

//sf::Sprite& Goal::getSprite(int i) {
//
//	return m_goalSprite[i];
//}