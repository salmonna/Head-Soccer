#pragma once
#include "MovingObject.h"
#include "Window.h"

class Player : public MovingObject
{
public:
	Player();

	virtual void draw(sf::RenderWindow& window) override;


	~Player() = default;

private:

};