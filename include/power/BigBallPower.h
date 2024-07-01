#pragma once
#include "Power.h"

class BigBallPower : public Power
{
public:

	BigBallPower(bool playerSide);

	virtual void activatePowerOnPlayer(Player* player)override;
	virtual void activatePowerOnBall(b2Body* ballBody) override;

	~BigBallPower() = default;

private:

	bool m_playerSide;

};
