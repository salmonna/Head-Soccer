#pragma once
#include "gameObject/MovingObject.h"


class Ball;

class MoveBehavior
{
public:
	MoveBehavior() = default;

	virtual void performMove(Ball * ball) = 0;

	~MoveBehavior() = default;

private:

};



