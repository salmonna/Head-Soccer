#pragma once
#include "Window.h"
#include "MoveBehavior.h"
#include <SFML/Graphics.hpp>
#include "Box2d.h"

class Power 
{
public:
	Power();
	
	void drawAura(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f origin);
	sf::Sprite& getSprite();
	virtual ~Power() = default;

	virtual void activatePowerOnBall(b2Body* ballBody) = 0;
	virtual void draw(sf::RenderWindow & window, sf::Vector2f position) {};

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



