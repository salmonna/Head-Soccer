#pragma once
#include "Power.h"

class FirePower : public Power
{
public:

	FirePower();

	void draw(sf::RenderWindow & window) const override;

	//--------------After Create Behavior------------------------------
	virtual void performMove(Ball * ball) override ;

	void activatePower(sf::CircleShape& ball, sf::Vector2f& currVelocity, sf::Vector2f & direction);
	virtual sf::Texture& getTexture() override;

	~FirePower() = default;

private:

	sf::Vector2f m_ballVelocity;
	sf::Clock m_clock;

};
