#include"MovePlayerState/StandPlayerState.h"
#include <iostream>

//----------------------------------------------------------------------------------
StandPlayerState::StandPlayerState(LeftMoveState* leftMoveState, RightMoveState* rightMoveState, JumpMoveState* jumeMoveState, KickMoveState* kickMoveState)
	:m_leftMoveState(leftMoveState), m_rightMoveState(rightMoveState),m_jumpMoveState(jumeMoveState),m_kickMoveState(kickMoveState), m_nextState(nullptr)
{
	
}

//----------------------------------------------------------------------------------
void StandPlayerState::movement(sf::Sprite& sprite, Keyboard key, b2Body* body) {

	resetToPosition(sprite);
	body->SetLinearVelocity(b2Vec2(0.f, body->GetLinearVelocity().y));

	if (sf::Keyboard::isKeyPressed(key.SPACE)) {//kick

		m_nextState = m_kickMoveState;
	}
	else if (sf::Keyboard::isKeyPressed(key.LEFT)) {//move left

		m_nextState = m_leftMoveState;
	}
	else if (sf::Keyboard::isKeyPressed(key.RIGHT)) {//move right

		m_nextState = m_rightMoveState;
	}
	else if (sf::Keyboard::isKeyPressed(key.JUMP)) {//jump
		body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, 0.f));
		m_nextState = m_jumpMoveState;
	}
	else {
		body->SetLinearVelocity(b2Vec2(0.f, body->GetLinearVelocity().y));  // Stop horizontal movement when no key is pressed
	}

}
//----------------------------------------------------------------------------------
BaseMovePlayerState* StandPlayerState::handleMoveStatus() {
	
	BaseMovePlayerState* temp = m_nextState;
	m_nextState = nullptr;
	return temp;
}

//----------------------------------------------------------------------------------
StandPlayerState::~StandPlayerState()
{
}