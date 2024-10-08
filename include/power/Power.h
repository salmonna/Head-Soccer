#pragma once
#include "Window.h"
#include <SFML/Graphics.hpp>
#include "Box2d.h"
#include "FileException.h"


class Ball;
class Player;

class Power 
{
public:
	Power();
	
	void drawAura(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f origin);
	sf::Sprite& getSprite();
	virtual ~Power() = default;

	virtual void activatePowerOnPlayer(Player* player) = 0;
	virtual void activatePowerOnBall(Ball* ball) = 0;
	virtual void animation(sf::Vector2f position) = 0;
	virtual void draw(sf::RenderWindow & window) const = 0;

	virtual bool powerIsActive();
	virtual void startTimer();
	virtual void checkTimeIsOver();
	virtual bool stayInTheAir();
	virtual bool getSideOfPlayer() const { return false; };

	void setPowerIsActive(bool powerIsActive);
private:

	bool m_powerIsActive;
	sf::Sprite m_auraSprite;
	sf::Clock m_clock;
	sf::Clock m_powerTimer;
	sf::Clock m_stayTimer;
};



