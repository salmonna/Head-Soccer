#pragma once
#include "Window.h"

class GameObject
{
public:
	GameObject() = default;

	virtual void draw(sf::RenderWindow& window) = 0;



	//update score
	virtual void timeCalculation() = 0;
	virtual void updateScore(int p1Points, int p2Points) = 0;
	virtual bool timeIsOver() = 0;

	~GameObject() = default;

private:

};



