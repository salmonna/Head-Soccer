#pragma once
#include "gameObject/MovingObject.h"


class MoveBehavior
{
public:
	MoveBehavior() = default;

	virtual void performMove(MovingObject * movingObject) = 0;

	~MoveBehavior() = default;

private:

};



