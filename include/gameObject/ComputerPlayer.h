#pragma once
#include "gameObject/MovingObject.h"

class ComputerPlayer :public MovingObject 
{
public:
	ComputerPlayer();
	~ComputerPlayer();

	virtual void move(sf::Vector2f pressed) override{};
	virtual void draw(sf::RenderWindow& window)const override{};

	void updateComputerPlayer(sf::RectangleShape& computer, sf::CircleShape& ball,
							  sf::RectangleShape& computerGoal, float deltaTime);

private:

	sf::Vector2f m_velocity;
};

