#pragma once
#include "Power.h"

class FirePower : public Power
{
public:

	FirePower();

	void activatePower(sf::CircleShape& ball, sf::Vector2f& currVelocity, sf::Vector2f & direction);

	~FirePower() = default;

private:

	sf::Vector2f m_ballVelocity;
	sf::Clock m_clock;

};
