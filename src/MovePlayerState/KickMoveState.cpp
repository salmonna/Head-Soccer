#include "MovePlayerState/KickMoveState.h"
#include "MovePlayerState/JumpMoveState.h"
#include "MovePlayerState/StandPlayerState.h"

//-------------------------------------------------------------------------
KickMoveState::KickMoveState():m_currentState(nullptr)
{
	m_startPos = sf::Vector2f(160, 126);
}
//-------------------------------------------------------------------------
void KickMoveState::movement(sf::Sprite& sprite, Keyboard key, b2Body* body) {

	movePlayer(m_startPos, 7, 10, sprite, sf::Vector2f(80, 95));

	if (changeState(7)) {

		if (sprite.getPosition().y < 750) {

			m_currentState = std::make_unique<JumpMoveState>(true);
		}
		else
		{
			m_currentState = std::make_unique<StandPlayerState>();
		}
	}

}
//-------------------------------------------------------------------------
std::unique_ptr<BaseMovePlayerState> KickMoveState::handleMoveStatus() {

	std::unique_ptr<BaseMovePlayerState> temp = std::move(m_currentState);

	return temp;
}
//-------------------------------------------------------------------------
KickMoveState::~KickMoveState()
{
}