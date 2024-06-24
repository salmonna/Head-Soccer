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
	StandPlayerState(LeftMoveState * leftMoveState , RightMoveState* rightMoveState , JumpMoveState* jumeMoveState ,KickMoveState * kickMoveState);
	virtual ~StandPlayerState();

	virtual BaseMovePlayerState* handleMoveStatus() override;
	virtual void movement(sf::Sprite& sprite, bool playerSide, b2Body* body)override;
	void setKeyboard(bool playerSide);

private:

	BaseMovePlayerState * m_nextState;
	LeftMoveState* m_leftMoveState;
	RightMoveState* m_rightMoveState;
	JumpMoveState* m_jumpMoveState;
	KickMoveState* m_kickMoveState;
	Keyboard m_keys;
};

