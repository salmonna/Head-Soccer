#include "MovePlayerState/JumpMoveState.h"

//----------------------------------------------------------------------------------
JumpMoveState::JumpMoveState(StandPlayerState* standState, KickMoveState* kickMoveState) :m_currentState(nullptr),
m_standMoveState(standState),m_kickMoveState(kickMoveState),m_jump(false)
{
	m_startPos = sf::Vector2f(160, 8);
}

//----------------------------------------------------------------------------------
void JumpMoveState::movement(sf::Sprite& sprite, bool playerSide, b2Body* body) {

	if (playerSide) {
		m_keys = Keyboard(sf::Keyboard::Space, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Down);
	}
	else {
		m_keys = Keyboard(sf::Keyboard::Q, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, sf::Keyboard::S);
	}

	b2Vec2 vel = body->GetLinearVelocity();
	if (!m_jump) {  // Check if player is on the ground
		body->ApplyLinearImpulseToCenter(b2Vec2(0.f, -JUMP_FORCE), true);
		m_jump = true;
	}

	movePlayer(m_startPos, 7, 160, sprite);

	if (changeState(7))
	{
		//m_body->SetLinearVelocity(b2Vec2(m_body->GetLinearVelocity().x, 0.f));
		m_currentState = (BaseMovePlayerState*)m_standMoveState;
		m_jump = false;
	}

	if (sf::Keyboard::isKeyPressed(m_keys.LEFT)) {//move left

		body->SetLinearVelocity(b2Vec2(-5.f, body->GetLinearVelocity().y));
	}
	else if (sf::Keyboard::isKeyPressed(m_keys.RIGHT)) {//move right

		body->SetLinearVelocity(b2Vec2(5.f, body->GetLinearVelocity().y));
	}
	else if (sf::Keyboard::isKeyPressed(m_keys.SPACE)) {//move right

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