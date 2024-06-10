#pragma once
#include "MovingObject.h"

class ComputerPlayer :public MovingObject 
{
public:
	ComputerPlayer();
	~ComputerPlayer();

	virtual void move(int keyPressed) override{};
	virtual void draw(sf::RenderWindow& window) override{};

	void updateComputerPlayer(sf::RectangleShape& computer, sf::CircleShape& ball,
							  sf::RectangleShape& computerGoal, float deltaTime);

private:

	sf::Vector2f m_velocity;
};

