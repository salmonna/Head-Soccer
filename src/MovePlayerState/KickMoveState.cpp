#include "MovePlayerState/KickMoveState.h"
#include "MovePlayerState/JumpMoveState.h"
#include "MovePlayerState/StandPlayerState.h"

//-------------------------------------------------------------------------
// Constructor for KickMoveState initializes kick state and starting position.
KickMoveState::KickMoveState():m_currentState(nullptr)
{
	m_startPos = sf::Vector2f(160, 126);
}
//-------------------------------------------------------------------------
// Handles movement logic for kicking state,
//  checks state changes to either jump or stand based on conditions.
void KickMoveState::movement(sf::Sprite& sprite, Keyboard , b2Body*) {

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
// Returns a unique pointer to the current player state and resets the current state to null.
std::unique_ptr<BaseMovePlayerState> KickMoveState::handleMoveStatus() {

	std::unique_ptr<BaseMovePlayerState> temp = std::move(m_currentState);

	return temp;
}
//-------------------------------------------------------------------------
KickMoveState::~KickMoveState()
{
}