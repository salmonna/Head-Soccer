#include "MovePlayerState/RightMoveState.h"
//---------------------------------------------------------
RightMoveState::RightMoveState(StandPlayerState* standMoveState):m_currentState(nullptr),m_standMoveState(standMoveState)
{
	m_startPos = sf::Vector2f(160, 244);
}
//---------------------------------------------------------
void RightMoveState::movement(sf::Sprite& sprite, sf::Vector2i& pos, sf::Vector2f basePos , int& gravity, bool playerSide) {

	moveWithRange(5,pos,playerSide);
	movePlayer(m_startPos, 6, 10,sprite,pos, basePos);
	updateGravityAndCollision(sprite, basePos, pos, gravity);


	if (changeState(6)) {

		m_currentState = (BaseMovePlayerState*)m_standMoveState;
	}
}
//---------------------------------------------------------
BaseMovePlayerState* RightMoveState::handleMoveStatus() {
	BaseMovePlayerState* temp = m_currentState;
	m_currentState = nullptr;

	return temp;
}
//---------------------------------------------------------
RightMoveState::~RightMoveState()
{
}