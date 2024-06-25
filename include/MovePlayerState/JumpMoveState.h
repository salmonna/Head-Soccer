#pragma once
#include "MovePlayerState/BaseMovePlayerState.h"
#include "MovePlayerState/LeftMoveState.h"
#include "MovePlayerState/RightMoveState.h"
#include "MovePlayerState/KickMoveState.h"
#include "Keyboard.h"

class StandPlayerState;

class JumpMoveState : public BaseMovePlayerState
{
public:
	JumpMoveState(StandPlayerState* standState,KickMoveState* kickMoveState);
	virtual ~JumpMoveState();

	virtual BaseMovePlayerState* handleMoveStatus() override;
	virtual void movement(sf::Sprite& sprite, bool playerSide, b2Body* body)override;

private:

	sf::Vector2f m_startPos;
	StandPlayerState* m_standMoveState;
	BaseMovePlayerState* m_currentState;
	KickMoveState* m_kickMoveState;

	Keyboard m_keys;

	bool m_jump;

};

