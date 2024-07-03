#pragma once
#include "Power.h"

class FistPower : public Power
{
public:

	FistPower(bool playerSide);

	virtual void activatePowerOnPlayer(Player* Player)override;
	virtual void activatePowerOnBall(Ball* ball) override;
	virtual void draw(sf::RenderWindow& window) const override;
	virtual void animation(sf::Vector2f position) override;
	virtual bool getSideOfPlayer()const override;

	~FistPower() = default;

private:

	bool m_playerSide;
	sf::Sprite m_sprite;


};
