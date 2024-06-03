

#pragma once
#include "Window.h"

class MovingObject
{
public:
	MovingObject();

	virtual void draw(sf::RenderWindow& window) = 0;

	virtual void move(int keyPressed) = 0;

	~MovingObject();

private:

};

