#pragma once
#include "Power.h"

class InvisiblePower : public Power
{
public:

	InvisiblePower(bool PlayerSide = true);
	virtual void activatePowerOnBall(Ball* ball)override;
	virtual void activatePowerOnPlayer(Player* player)override;
	bool getSideOfPlayer()const;
	virtual void animation(sf::Vector2f position) override {};
	virtual void draw(sf::RenderWindow& window) const override {};
	~InvisiblePower() = default;

private:
	bool m_PlayerSide;

};
