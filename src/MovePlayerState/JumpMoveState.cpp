#include "MovePlayerState/JumpMoveState.h"

//----------------------------------------------------------------------------------
JumpMoveState::JumpMoveState(StandPlayerState* standState, KickMoveState* kickMoveState) :m_currentState(nullptr),
m_standMoveState(standState),m_kickMoveState(kickMoveState),m_jump(false)
{
	m_startPos = sf::Vector2f(160, 8);
}

//----------------------------------------------------------------------------------
void JumpMoveState::movement(sf::Sprite& sprite, Keyboard key, b2Body* body) {

	b2Vec2 vel = body->GetLinearVelocity();
	if (!m_jump) {  // Check if Player is on the ground
		body->ApplyLinearImpulseToCenter(b2Vec2(0.f, -JUMP_FORCE), true);
		m_jump = true;
	}

	movePlayer(m_startPos, 7, 160, sprite, sf::Vector2f(70, 95));

	if (changeState(7))
	{
		m_currentState = (BaseMovePlayerState*)m_standMoveState;
		m_jump = false;
	}

	if (sf::Keyboard::isKeyPressed(key.LEFT)) {//move left

		body->SetLinearVelocity(b2Vec2(-5.f, body->GetLinearVelocity().y));
	}
	else if (sf::Keyboard::isKeyPressed(key.RIGHT)) {//move right

		body->SetLinearVelocity(b2Vec2(5.f, body->GetLinearVelocity().y));
	}
	else if (sf::Keyboard::isKeyPressed(key.SPACE)) {//move right

		m_currentState = m_kickMoveState;
	}

}

//----------------------------------------------------------------------------------
BaseMovePlayerState* JumpMoveState::handleMoveStatus()
{
	BaseMovePlayerState* temp = m_currentState;
	m_currentState = nullptr;

	return temp;

}
//----------------------------------------------------------------------------------
JumpMoveState::~JumpMoveState()
{
}