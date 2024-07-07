#include"MovePlayerState/StandPlayerState.h"
#include <iostream>

//----------------------------------------------------------------------------------
StandPlayerState::StandPlayerState():m_nextState(nullptr)
{
}

//----------------------------------------------------------------------------------
// Handles player movement based on keyboard input, resetting position and setting next state.
void StandPlayerState::movement(sf::Sprite& sprite, Keyboard key, b2Body* body) {

	resetToPosition(sprite);
	body->SetLinearVelocity(b2Vec2(0.f, body->GetLinearVelocity().y));

	if (sf::Keyboard::isKeyPressed(key.SPACE)) {//kick

		m_nextState = std::make_unique<KickMoveState>();
	}
	else if (sf::Keyboard::isKeyPressed(key.LEFT)) {//move left

		m_nextState = std::make_unique<LeftMoveState>();
	}
	else if (sf::Keyboard::isKeyPressed(key.RIGHT)) {//move right

		m_nextState = std::make_unique<RightMoveState>();
	}
	else if (sf::Keyboard::isKeyPressed(key.JUMP)) {//jump
		body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, 0.f));
		m_nextState = std::make_unique<JumpMoveState>(false);
	}
	else {
		body->SetLinearVelocity(b2Vec2(0.f, body->GetLinearVelocity().y));  // Stop horizontal movement when no key is pressed
	}

}
//----------------------------------------------------------------------------------
// Retrieves the next move state and transfers ownership to the caller.
std::unique_ptr<BaseMovePlayerState> StandPlayerState::handleMoveStatus() {
	
	std::unique_ptr<BaseMovePlayerState> temp = std::move(m_nextState);
	return temp;
}
//----------------------------------------------------------------------------------
StandPlayerState::~StandPlayerState()
{
}