#pragma once
#include "Power.h"

class FirePower : public Power
{
public:

	FirePower(bool playerSide = true);

	virtual void activatePowerOnPlayer(Player* player)override;
	virtual void activatePowerOnBall(Ball* ball) override;
	virtual void draw(sf::RenderWindow& window, sf::Vector2f position) override;
	virtual bool getSideOfPlayer() const override;

	~FirePower() = default;

private:

	sf::Clock m_spriteSheetClock;
	std::vector<std::pair<sf::Vector2i, sf::Vector2i>> m_spriteSheet;
	std::vector<std::pair<sf::Vector2i, sf::Vector2i>> m_spriteSheetFlame;
	int m_index1;
	int m_index2;
	sf::Sprite m_sprite;
	bool m_playerSide;
};
