#pragma once
#include "Power.h"

class InvisiblePower : public Power
{
public:

	InvisiblePower();

	virtual void activatePowerOnBall(Ball* ball)override;

	~InvisiblePower() = default;

private:

};
