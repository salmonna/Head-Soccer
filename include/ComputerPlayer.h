#pragma once
#include "MovingObject.h"

class ComputerPlayer :public MovingObject
{
public:
	ComputerPlayer();
	~ComputerPlayer();

	virtual void move(int keyPressed) override{};
	virtual void draw(sf::RenderWindow& window) override{};

	void updateComputerPlayer(/*sf::RectangleShape& player, sf::Vector2f& ballvelocity,*/ sf::CircleShape& ball,
		sf::RectangleShape& userGoal, /* float deltaTime*/);

private:

	sf::Vector2f m_velocity;
	sf::Sprite m_comPlayerSprite;
};

