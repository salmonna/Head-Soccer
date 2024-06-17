#pragma once
#include "Power.h"

class FirePower : public Power
{
public:

	FirePower(sf::Vector2f pos);

	void draw(sf::RenderWindow & window) const override;

	virtual void activatePower(sf::Sprite& ball, sf::Sprite& player) override;


	~FirePower() = default;

private:



};
