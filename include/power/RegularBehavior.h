#pragma once
#include "MoveBehavior.h"


class RegularBehavior : public MoveBehavior
{
public:
	RegularBehavior();

	virtual void performMove(Ball * ball) override ;

	~RegularBehavior() = default;

private:
	sf::Vector2f m_ballVelocity;
	sf::Clock m_clock;

};
