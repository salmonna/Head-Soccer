#pragma once
#include "Power.h"

class AvatarPower : public Power
{
public:

	AvatarPower(bool PlayerSide = true);

	virtual void activatePowerOnPlayer(Player* player)override;
	virtual void activatePowerOnBall(Ball* ball) override;
	virtual void animation(sf::Vector2f position) override;
	virtual void draw(sf::RenderWindow& window) const override;
	virtual bool getSideOfPlayer() const override;


	~AvatarPower() = default;

private:
	sf::Clock m_spriteSheetClock;
	std::vector<std::pair<sf::Vector2i, sf::Vector2i>> m_spriteSheet;
	int m_index;
	sf::Sprite m_sprite;
	bool m_PlayerSide;

};
