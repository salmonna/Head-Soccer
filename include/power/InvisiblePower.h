#pragma once
#include "Power.h"

class InvisiblePower : public Power
{
public:

	InvisiblePower();

	void activatePower(sf::CircleShape& ball, sf::Vector2f& currVelocity, sf::Vector2f& direction);

	~InvisiblePower() = default;

private:

};
