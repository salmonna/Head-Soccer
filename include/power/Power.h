#pragma once
#include "Window.h"
#include "MoveBehavior.h"
#include <SFML/Graphics.hpp>

class Power 
{
public:
	Power();
	
	void drawAura(sf::RenderWindow& window, sf::Vector2f position);
	sf::Sprite& getSprite();
	virtual ~Power() = default;

	virtual void activatePower(sf::CircleShape& ball, sf::Vector2f& currVelocity, sf::Vector2f& direction) = 0;

	virtual bool powerIsActive();
	virtual void startTimer();
	virtual bool isTimeIsOver();
	virtual bool stayInTheAir();

	void setPowerIsActive(bool powerIsActive);
private:
	bool m_powerIsActive;
	sf::Sprite m_auraSprite;
	sf::Clock m_clock;
	sf::Clock m_powerTimer;
	sf::Clock m_stayTimer;
};



