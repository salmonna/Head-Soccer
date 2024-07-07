#pragma once
#include "MovePlayerState/BaseMovePlayerState.h"
#include "MovePlayerState/LeftMoveState.h"
#include "MovePlayerState/RightMoveState.h"
#include "MovePlayerState/JumpMoveState.h"
#include "MovePlayerState/KickMoveState.h"
#include "Keyboard.h"

class StandPlayerState: public BaseMovePlayerState
{
public:
	StandPlayerState();
	virtual ~StandPlayerState();

	virtual std::unique_ptr<BaseMovePlayerState> handleMoveStatus() override;
	virtual void movement(sf::Sprite& sprite, Keyboard key, b2Body* body)override;

private:

	std::unique_ptr<BaseMovePlayerState> m_nextState;
};

