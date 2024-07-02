#pragma once
#include "Power.h"

class ElectricPower : public Power
{
public:

	ElectricPower(bool PlayerSide);

	virtual void activatePowerOnPlayer(Player* Player)override;
	virtual void activatePowerOnBall(Ball* ball) override;
	virtual void draw(sf::RenderWindow& window, sf::Vector2f position) override;
	bool getSideOfPlayer()const;

	~ElectricPower() = default;

private:
	sf::Clock m_spriteSheetClock;
	std::vector<std::pair<sf::Vector2i, sf::Vector2i>> m_spriteSheet;
	int m_index;
	sf::Sprite m_sprite;
	bool m_PlayerSide;


};
