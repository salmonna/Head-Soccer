#pragma once
#include "Power.h"

class BigBallPower : public Power
{
public:

	BigBallPower(bool playerSide);

	virtual void activatePowerOnPlayer(Player* player)override;
	virtual void activatePowerOnBall(Ball* ball) override;
	virtual bool getSideOfPlayer()const override;

	~BigBallPower() = default;

private:

	bool m_playerSide;

};
