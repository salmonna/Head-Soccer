#pragma once
#include "GameObject.h"



class StaticObject : public GameObject
{
public:
	StaticObject() {};

	virtual void draw(sf::RenderWindow & window) = 0;



	~StaticObject() = default;

private:

};
