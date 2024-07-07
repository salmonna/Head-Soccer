
#pragma once
#include  "GameObject.h"
#include "MovePlayerState/BaseMovePlayerState.h"

class MovingObject:public GameObject
{
public:
	MovingObject() = default;

	virtual void move() = 0;
	virtual void reset() = 0;

	sf::Vector2f B2VecToSFVec(const b2Vec2& vector);
	
	~MovingObject() = default;

private:

};

