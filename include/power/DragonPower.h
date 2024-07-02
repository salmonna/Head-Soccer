#pragma once
#include"power/Power.h"

class DragonPower:public Power
{
public:
	DragonPower();
	~DragonPower();

	virtual void activatePowerOnBall(Ball* ball)override;
	virtual void draw(sf::RenderWindow& window, sf::Vector2f position) override;
private:

	void dragonRect(std::pair<sf::Vector2i, sf::Vector2i> it);
	std::vector<std::pair<sf::Vector2i, sf::Vector2i>> m_posDragon;
	sf::Sprite m_dragonSprite;

	sf::Clock m_clockDragon;

	int m_round;
	bool m_rightSide;
};
