#pragma once
#include "Power.h"

class KameHameHaPower : public Power
{
public:

	KameHameHaPower();

	void activatePower(sf::CircleShape& ball, sf::Vector2f& currVelocity, sf::Vector2f& direction);
	virtual void draw(sf::RenderWindow& window, sf::Vector2f position) override;


	~KameHameHaPower() = default;

private:
	sf::Clock m_spriteSheetClock;
	std::vector<std::pair<sf::Vector2i, sf::Vector2i>> m_spriteSheet;
	int m_index;
	sf::Sprite m_sprite;


};
