#pragma once
#include "Power.h"

class InvisiblePower : public Power
{
public:

	InvisiblePower(bool playerSide = true);
	virtual void activatePowerOnBall(Ball* ball)override;
	virtual void activatePowerOnPlayer(Player* player)override;
	bool getSideOfPlayer()const;
	~InvisiblePower() = default;

private:
	bool m_playerSide;

};
