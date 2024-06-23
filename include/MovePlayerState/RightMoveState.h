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

	virtual void movement(sf::Sprite& sprite, sf::Vector2i& pos, sf::Vector2f basePos, int& gravity, bool playerSide, b2Body* m_body) override;
	virtual BaseMovePlayerState* handleMoveStatus() override;

private:

	sf::Vector2f m_startPos;
	StandPlayerState* m_standMoveState;
	JumpMoveState* m_jumpMoveState;
	BaseMovePlayerState* m_currentState;

	Keyboard m_keys;
};

