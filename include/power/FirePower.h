#pragma once
#include "Power.h"

class FirePower : public Power
{
public:

	FirePower();

	void activatePower(sf::CircleShape& ball, sf::Vector2f& currVelocity, sf::Vector2f & direction);
	virtual void draw(sf::RenderWindow& window, sf::Vector2f position) override;

	~FirePower() = default;

private:

	sf::Vector2f m_ballVelocity;
	sf::Clock m_clock;
	sf::Clock m_spriteSheetClock;
	std::vector<std::pair<sf::Vector2i, sf::Vector2i>> m_spriteSheet;
	std::vector<std::pair<sf::Vector2i, sf::Vector2i>> m_spriteSheetFlame;
	int m_index1;
	int m_index2;
	sf::Sprite m_sprite;

};
