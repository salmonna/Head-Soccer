#pragma once
#include "MovePlayerState/BaseMovePlayerState.h"

class StandPlayerState;

class RightMoveState : public BaseMovePlayerState
{
public:
	RightMoveState(StandPlayerState * standMoveState);
	virtual ~RightMoveState();

	virtual void movement(sf::Sprite& sprite, sf::Vector2i& pos, sf::Vector2f basePos, int& gravity, bool playerSide) override;
	virtual BaseMovePlayerState* handleMoveStatus() override;

private:

	sf::Vector2f m_startPos;
	StandPlayerState* m_standMoveState;
	BaseMovePlayerState* m_currentState;
};

