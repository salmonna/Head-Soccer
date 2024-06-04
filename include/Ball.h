#pragma once
#include "MovingObject.h"
#include "Window.h"

class Ball : public MovingObject
{
public:
	Ball();

	virtual void draw(sf::RenderWindow& window) override;


	~Ball() = default;

private:

};

