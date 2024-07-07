#pragma once
#include "MovePlayerState/BaseMovePlayerState.h"

class JumpMoveState : public BaseMovePlayerState
{
public:
	JumpMoveState(bool jump);
	virtual ~JumpMoveState();

	virtual std::unique_ptr<BaseMovePlayerState> handleMoveStatus()override;
	virtual void movement(sf::Sprite& sprite, Keyboard key, b2Body* body)override;

private:

	sf::Vector2f m_startPos;
	std::unique_ptr<BaseMovePlayerState> m_currentState;
	bool m_jump;
};

