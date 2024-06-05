#pragma once
#include "Window.h"

class GameObject
{
public:
	GameObject() = default;

	virtual void draw(sf::RenderWindow& window) = 0;

	~GameObject() = default;

private:

};



