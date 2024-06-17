#pragma once
#include "Power.h"

class FirePower : public Power
{
public:

	FirePower(sf::Vector2f pos);

	void draw(sf::RenderWindow & window) const override;

	~FirePower() = default;

private:



};
