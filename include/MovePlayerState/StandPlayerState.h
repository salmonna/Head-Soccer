#pragma once
#include "MovePlayerState/BaseMovePlayerState.h"
#include "MovePlayerState/LeftMoveState.h"
#include "MovePlayerState/RightMoveState.h"
#include "Keyboard.h"

class StandPlayerState: public BaseMovePlayerState
{
public:
	StandPlayerState(LeftMoveState * leftMoveState , RightMoveState* rightMoveState);
	~StandPlayerState();

	virtual BaseMovePlayerState* handleMoveStatus() override;
	virtual void movement(sf::Sprite& sprite, sf::Vector2i& pos, sf::Vector2f basePos, int& gravity) override;

private:

	BaseMovePlayerState * m_nextState;
	LeftMoveState* m_leftMoveState;
	RightMoveState* m_rightMoveState;
	Keyboard m_keys;
};

