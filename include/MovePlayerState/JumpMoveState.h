#pragma once
#include "MovePlayerState/BaseMovePlayerState.h"
#include "MovePlayerState/LeftMoveState.h"
#include "MovePlayerState/RightMoveState.h"
#include "MovePlayerState/KickMoveState.h"

class StandPlayerState;

class JumpMoveState : public BaseMovePlayerState
{
public:
	JumpMoveState(StandPlayerState* standState,KickMoveState* kickMoveState);
	virtual ~JumpMoveState();

	virtual BaseMovePlayerState* handleMoveStatus() override;
	virtual void movement(sf::Sprite& sprite, Keyboard key, b2Body* body)override;

private:

	sf::Vector2f m_startPos;
	StandPlayerState* m_standMoveState;
	BaseMovePlayerState* m_currentState;
	KickMoveState* m_kickMoveState;

	bool m_jump;
};

