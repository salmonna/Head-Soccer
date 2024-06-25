#pragma once
#include "MovePlayerState/BaseMovePlayerState.h"
#include "Keyboard.h"

class StandPlayerState;
class JumpMoveState;

class RightMoveState : public BaseMovePlayerState
{
public:
	RightMoveState(StandPlayerState * standMoveState, JumpMoveState* jumpMoveState);
	virtual ~RightMoveState();

	virtual void movement(sf::Sprite& sprite, bool playerSide, b2Body* body) override;
	virtual BaseMovePlayerState* handleMoveStatus() override;

private:

	sf::Vector2f m_startPos;
	StandPlayerState* m_standMoveState;
	JumpMoveState* m_jumpMoveState;
	BaseMovePlayerState* m_currentState;

	Keyboard m_keys;
};

