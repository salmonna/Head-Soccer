#pragma once 
#include "power/Power.h"

class DuplicateBall : public Power
{
public:
	DuplicateBall();
	~DuplicateBall();

	virtual void activatePowerOnBall(Ball* ball) override;
	virtual void draw(sf::RenderWindow& window, sf::Vector2f position);

	void resetPos(sf::Vector2f& position);

private:

	std::vector<sf::Sprite> m_ballSprites;

	sf::Vector2f m_direction;
	float m_velocity;

	bool m_isIntiliaz;
};
