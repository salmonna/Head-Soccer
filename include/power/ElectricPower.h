#pragma once
#include "Power.h"

class ElectricPower : public Power
{
public:

	ElectricPower();

	virtual void activatePowerOnPlayer(Player* player) {};
	virtual void activatePowerOnBall(b2Body* ballBody) override {};
	virtual void draw(sf::RenderWindow& window, sf::Vector2f position) override;


	~ElectricPower() = default;

private:
	sf::Clock m_spriteSheetClock;
	std::vector<std::pair<sf::Vector2i, sf::Vector2i>> m_spriteSheet;
	int m_index;
	sf::Sprite m_sprite;


};
