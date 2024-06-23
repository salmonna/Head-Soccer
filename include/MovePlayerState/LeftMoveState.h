#pragma once
#include "MovePlayerState/BaseMovePlayerState.h"

class StandPlayerState;

class LeftMoveState : public BaseMovePlayerState
{
public:
	LeftMoveState(StandPlayerState* standMoveState);
	~LeftMoveState();

	virtual void movement(sf::Sprite& sprite, sf::Vector2i& pos, sf::Vector2f basePos, int& gravity, bool playerSide, b2Body* m_body) override;
	virtual BaseMovePlayerState* handleMoveStatus() override;

private:

	sf::Vector2f m_startPos;
	StandPlayerState* m_standMoveState;
	BaseMovePlayerState* m_currentState;
};

