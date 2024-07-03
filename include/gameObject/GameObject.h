#pragma once
#include "Window.h"
#include "Box2d.h"

class GameObject
{
public:
	GameObject() = default;

	virtual void draw(sf::RenderWindow& window) const = 0;
	virtual sf::Sprite& getSprite() = 0;
	virtual b2Body* getBody() const  { return nullptr; };


	~GameObject() = default;

private:

};



