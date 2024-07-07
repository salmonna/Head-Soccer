#pragma once

#include"MovePlayerState/BaseMovePlayerState.h"


class KickMoveState :public BaseMovePlayerState
{
public:
	KickMoveState();
	~KickMoveState();

	virtual void movement(sf::Sprite& sprite, Keyboard key, b2Body* body) override;
	virtual std::unique_ptr<BaseMovePlayerState> handleMoveStatus() override;

private:

	sf::Vector2f m_startPos;
	std::unique_ptr<BaseMovePlayerState> m_currentState;
};

