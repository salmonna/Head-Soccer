#pragma once
#include "Window.h"
#include "MoveBehavior.h"
#include <SFML/Graphics.hpp>

class Power : public MoveBehavior
{
public:
	Power();
	
	virtual void draw(sf::RenderWindow& window) const = 0;
	void drawAura(sf::RenderWindow& window, sf::Vector2f position);
	sf::Sprite& getSprite();
	virtual sf::Texture& getTexture() = 0;
	virtual ~Power() = default;

	virtual void activatePower(sf::CircleShape& ball, sf::Vector2f& currVelocity, sf::Vector2f& direction) = 0;
	virtual void startTimer();
	virtual bool isTimeIsOver();

private:
	sf::Sprite m_auraSprite;
	sf::Clock m_clock;
	sf::Clock m_powerTimer;
};



