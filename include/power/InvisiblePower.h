#pragma once
#include "Power.h"

class InvisiblePower : public Power
{
public:

	InvisiblePower();

	virtual void activatePowerOnBall(b2Body* ballBody)override;

	~InvisiblePower() = default;

private:

};
