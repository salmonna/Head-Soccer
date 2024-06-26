#pragma once
#include "Power.h"

class BigBallPower : public Power
{
public:

	BigBallPower();

	void activatePower(sf::CircleShape& ball, sf::Vector2f& currVelocity, sf::Vector2f& direction);

	~BigBallPower() = default;

private:
};
