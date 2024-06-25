#pragma once 
#include "power/Power.h"

class DuplicateBall : public Power
{
public:
	DuplicateBall();
	~DuplicateBall();

	virtual void activatePower(sf::CircleShape& ball, sf::Vector2f& currVelocity, sf::Vector2f& direction) override;
	virtual void draw(sf::RenderWindow& window, sf::Vector2f position);

private:

	std::vector<sf::Sprite> m_ballSprites;
};
