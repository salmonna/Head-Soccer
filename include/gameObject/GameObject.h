#pragma once
#include "Window.h"

class GameObject
{
public:
	GameObject() = default;

	virtual void draw(sf::RenderWindow& window) const = 0;

	virtual sf::Sprite& getSprite() = 0;

	~GameObject() = default;

private:

};



