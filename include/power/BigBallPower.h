#pragma once
#include "Power.h"

class BigBallPower : public Power
{
public:

	BigBallPower();

	virtual void activatePowerOnBall(b2Body* ballBody)override;

	~BigBallPower() = default;

private:
};
