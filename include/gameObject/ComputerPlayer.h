#pragma once
#include "gameObject/MovingObject.h"

class ComputerPlayer :public MovingObject
{
public:
	ComputerPlayer();
	~ComputerPlayer();

	virtual void move(sf::Vector2f pressed) override{};
	virtual void draw(sf::RenderWindow& window)const override{};

	void updateComputerPlayer(/*sf::RectangleShape& player, sf::Vector2f& ballvelocity,*/ sf::CircleShape& ball,
		sf::RectangleShape& userGoal /* float deltaTime*/);

private:

	sf::Vector2f m_velocity;
	sf::Sprite m_comPlayerSprite;
};

