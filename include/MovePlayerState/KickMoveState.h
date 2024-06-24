#pragma once

#include"MovePlayerState/BaseMovePlayerState.h"

class StandPlayerState;
class JumpMoveState;

class KickMoveState :public BaseMovePlayerState
{
public:
	KickMoveState(StandPlayerState* standState,JumpMoveState* jumpMoveState);
	~KickMoveState();

	virtual void movement(sf::Sprite& sprite, bool playerSide, b2Body* body) override;
	virtual BaseMovePlayerState* handleMoveStatus() override;

private:

	sf::Vector2f m_startPos;
	StandPlayerState* m_standMoveState;
	JumpMoveState* m_jumpMoveState;
	BaseMovePlayerState* m_currentState;
};

