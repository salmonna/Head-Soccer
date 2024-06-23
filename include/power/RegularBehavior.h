#pragma once
#include "power/Power.h"


class RegularBehavior : public Power
{
public:
	RegularBehavior();

	virtual void activatePower(sf::CircleShape& ball, sf::Vector2f& currVelocity, sf::Vector2f& direction) override
	{


	};

	~RegularBehavior() = default;

private:
	sf::Vector2f m_ballVelocity;
	sf::Clock m_clock;

};
