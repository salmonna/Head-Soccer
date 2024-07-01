#pragma once
#include "power/Power.h"


class RegularBehavior : public Power
{
public:
	RegularBehavior();

	virtual void activatePowerOnBall(Ball * ball) override
	{


	};
	~RegularBehavior() = default;

private:
	sf::Vector2f m_ballVelocity;
	sf::Clock m_clock;

};
