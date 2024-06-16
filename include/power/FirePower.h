#pragma once
#include "Power.h"

class FirePower : public Power
{
public:
	FirePower();

	void draw(sf::RenderWindow & window) const override;

	~FirePower() = default;

private:

};
