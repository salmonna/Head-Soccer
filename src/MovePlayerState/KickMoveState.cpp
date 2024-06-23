#include "MovePlayerState/KickMoveState.h"

//-------------------------------------------------------------------------
KickMoveState::KickMoveState(StandPlayerState* standState, JumpMoveState* jumpMoveState):m_currentState(nullptr),
m_standMoveState(standState),m_jumpMoveState(jumpMoveState)
{
	m_startPos = sf::Vector2f(160, 126);
}
//-------------------------------------------------------------------------
void KickMoveState::movement(sf::Sprite& sprite, sf::Vector2i& pos, sf::Vector2f basePos, int& gravity, bool playerSide) {

	movePlayer(m_startPos, 7, 10, sprite, pos, basePos);

	if (changeState(7)) {

		if (sprite.getPosition().y < 750) {

			m_currentState = (BaseMovePlayerState*)m_jumpMoveState;
		}
		else
		{
			m_currentState = (BaseMovePlayerState*)m_standMoveState;
		}
	}

}
//-------------------------------------------------------------------------
BaseMovePlayerState* KickMoveState::handleMoveStatus() {

	BaseMovePlayerState* temp = m_currentState;
	m_currentState = nullptr;

	return temp;
}
//-------------------------------------------------------------------------
KickMoveState::~KickMoveState()
{
}