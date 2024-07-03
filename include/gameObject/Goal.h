#pragma once
#include "Resources.h"
#include "StaticObject.h"


class Goal : public StaticObject
{
public:
	Goal() {};
	
	virtual void draw(sf::RenderWindow& window) const override {};
	void setRightGoal() {};

	virtual ~Goal() = default;

private:

};
