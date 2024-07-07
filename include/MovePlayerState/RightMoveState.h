#pragma once
#include "MovePlayerState/BaseMovePlayerState.h"
#include "Keyboard.h"

class RightMoveState : public BaseMovePlayerState
{
public:
	RightMoveState();
	virtual ~RightMoveState();

	virtual void movement(sf::Sprite& sprite, Keyboard key, b2Body* body) override;
	virtual std::unique_ptr<BaseMovePlayerState> handleMoveStatus()override;

private:

	sf::Vector2f m_startPos;
	std::unique_ptr<BaseMovePlayerState> m_currentState;

};

