#include "MovePlayerState/LeftMoveState.h"
//----------------------------------------------------------
LeftMoveState::LeftMoveState(StandPlayerState* standMoveState):m_standMoveState(standMoveState),m_currentState(nullptr)
{
	m_startPos = sf::Vector2f(160, 244);
}
//----------------------------------------------------------
void LeftMoveState::movement(sf::Sprite& sprite, sf::Vector2i& pos, sf::Vector2f basePos, int& gravity, bool playerSide, b2Body* m_body) {

	m_body->SetLinearVelocity(b2Vec2(-5.f, m_body->GetLinearVelocity().y));
	//moveWithRange(-5,pos, playerSide);
	movePlayer(m_startPos, 6, 10,sprite,pos,basePos);

	if (changeState(6)) {

		m_currentState = (BaseMovePlayerState*)m_standMoveState;
	}
}
//----------------------------------------------------------
BaseMovePlayerState* LeftMoveState::handleMoveStatus() {

	BaseMovePlayerState* temp = m_currentState;
	m_currentState = nullptr;

	return temp;
}
//----------------------------------------------------------
LeftMoveState::~LeftMoveState()
{
}