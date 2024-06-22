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
	virtual void movement(sf::Sprite& sprite, sf::Vector2i& pos, sf::Vector2f basePos, int& gravity, bool playerSide)override;

private:

	void updateGravityAndCollision(sf::Sprite& sprite, sf::Vector2f basePos, sf::Vector2i& pos, int& gravity);
	sf::Vector2f m_startPos;
	StandPlayerState* m_standMoveState;
	BaseMovePlayerState* m_currentState;
	KickMoveState* m_kickMoveState;

	Keyboard m_keys;

};

