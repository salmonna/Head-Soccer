
#pragma once
#include  "GameObject.h"
#include "MovePlayerState/BaseMovePlayerState.h"

class MovingObject:public GameObject
{
public:
	MovingObject() = default;

	virtual void move(sf::Vector2f pressed) = 0;
	virtual void draw(sf::RenderWindow& window) const = 0;
	virtual sf::Vector2f getPosition() const = 0;
	virtual void reset() = 0;
	~MovingObject() = default;

private:

};

