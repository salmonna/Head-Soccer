#include "MovePlayerState/LeftMoveState.h"
#include "MovePlayerState/JumpMoveState.h"
#include "MovePlayerState/StandPlayerState.h"
#include <iostream>

//----------------------------------------------------------
LeftMoveState::LeftMoveState():m_currentState(nullptr)
{
	m_startPos = sf::Vector2f(160, 244);
}
//----------------------------------------------------------
void LeftMoveState::movement(sf::Sprite& sprite, Keyboard key, b2Body* body) {

	if (sf::Keyboard::isKeyPressed(key.JUMP))
	{
		body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, 0.f));
		m_currentState = std::make_unique<JumpMoveState>(false);
		return;
	}
	else {
		body->SetLinearVelocity(b2Vec2(-10.f, body->GetLinearVelocity().y));
		movePlayer(m_startPos, 6, 10, sprite, sf::Vector2f(80, 95));
	}
	if (changeState(6)) {

		m_currentState = std::make_unique<StandPlayerState>();
	}
}
//----------------------------------------------------------
std::unique_ptr<BaseMovePlayerState> LeftMoveState::handleMoveStatus() {

	std::unique_ptr<BaseMovePlayerState> temp = std::move(m_currentState);
	m_currentState = nullptr;

	return temp;
}
//----------------------------------------------------------
LeftMoveState::~LeftMoveState()
{
}