#pragma once
#include "Power.h"

class FirePower : public Power
{
public:

	FirePower(bool playerSide = true);

	virtual void activatePowerOnPlayer(b2Body* playerBody, sf::Sprite* sprite)override;
	virtual void activatePowerOnBall(b2Body* ballBody) override;
	virtual void draw(sf::RenderWindow& window, sf::Vector2f position) override;
	virtual bool getSideOfPlayer() const override;

	
	virtual void setPowerOnPlayer(bool powerOnPlayer)override;
	virtual bool getPowerOnPlayer()const override;

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
	bool m_powerOnPlayer;
	bool m_playerSide;
};
