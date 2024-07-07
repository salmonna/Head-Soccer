#pragma once
#include "gameObject/MovingObject.h"
#include "power/Power.h"

class Player :public MovingObject
{
public:
	Player();
	
	virtual bool getAura() const = 0;
	virtual void setAura(bool aura) = 0;
	virtual bool getSideOfPlayer()const = 0;
	virtual void setPowerOnPlayer(bool powerOnPlayer) = 0;
	virtual bool getPowerOnPlayer() const = 0;
	virtual std::shared_ptr<Power> getPower() const = 0;
	virtual void restartClock() = 0;

	void resetToPosition(sf::Sprite &sprite, sf::Vector2f basePosition, sf::Vector2f startPos = sf::Vector2f(160, 590),int numOfJump = 0);
	void deactivatePower(b2Body* body, sf::Sprite& sprite, sf::Color PlayerColor, bool& powerOnPlayer);
	virtual ~Player() = default;

private:

};


