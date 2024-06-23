#include "MovePlayerState/JumpMoveState.h"

//----------------------------------------------------------------------------------
JumpMoveState::JumpMoveState(StandPlayerState* standState, KickMoveState* kickMoveState) :m_currentState(nullptr),
m_standMoveState(standState),m_kickMoveState(kickMoveState),m_jump(false)
{
	m_startPos = sf::Vector2f(160, 8);
}

//----------------------------------------------------------------------------------
void JumpMoveState::movement(sf::Sprite& sprite, sf::Vector2i& pos, sf::Vector2f basePos, int& gravity, bool playerSide, b2Body* m_body) {

	if (playerSide) {
		m_keys = Keyboard(sf::Keyboard::Space, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Down);
	}
	else {
		m_keys = Keyboard(sf::Keyboard::Q, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, sf::Keyboard::S);
	}

	b2Vec2 vel = m_body->GetLinearVelocity();
	if (vel.y == 0 && !m_jump) {  // Check if player is on the ground
		m_body->ApplyLinearImpulseToCenter(b2Vec2(0.f, -JUMP_FORCE), true);
		m_jump = true;
	}
	
	if (m_jump)
	{
		movePlayer(m_startPos, 7, 272, sprite, pos, basePos);
	}
	else
	{
		m_currentState = (BaseMovePlayerState*)m_standMoveState;
	}
	
	//updateGravityAndCollision(sprite, basePos, pos, gravity);

	if (sf::Keyboard::isKeyPressed(m_keys.LEFT)) {//move left

		m_body->SetLinearVelocity(b2Vec2(-5.f, m_body->GetLinearVelocity().y));
	}
	else if (sf::Keyboard::isKeyPressed(m_keys.RIGHT)) {//move right

		m_body->SetLinearVelocity(b2Vec2(5.f, m_body->GetLinearVelocity().y));
	}
	else if (sf::Keyboard::isKeyPressed(m_keys.SPACE)) {//move right

		m_currentState = m_kickMoveState;
	}

	if (changeState(7))
	{
		//m_body->SetLinearVelocity(b2Vec2(m_body->GetLinearVelocity().x, 0.f));
		m_currentState = (BaseMovePlayerState*)m_standMoveState;
		m_jump = false;
	}
	
}
//----------------------------------------------------------------------------------
void JumpMoveState::updateGravityAndCollision(sf::Sprite& sprite, sf::Vector2f basePos, sf::Vector2i& pos, int& gravity) {

	if (sprite.getPosition().y < 750)
	{
		sprite.setPosition(float(basePos.x + pos.x), float(basePos.y + pos.y + gravity));
		gravity += 5;
	}
	else
	{
		gravity = 0;
		pos.y = 0;
		m_currentState = (BaseMovePlayerState*)m_standMoveState;
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