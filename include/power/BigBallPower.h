#pragma once
#include "Power.h"

class BigBallPower : public Power
{
public:

	BigBallPower();

	virtual void activatePowerOnBall(Ball* ball)override;

	~BigBallPower() = default;

private:
};
