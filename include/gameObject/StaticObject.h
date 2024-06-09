#pragma once
#include "GameObject.h"



class StaticObject : public GameObject
{
public:
	StaticObject() {};

	virtual void draw(sf::RenderWindow & window) = 0;

	////update score
	//virtual void timeCalculation() = 0;
	//virtual void updateScore(int p1Points, int p2Points) = 0;
	//virtual bool timeIsOver() = 0;

	~StaticObject() = default;

private:

};
