#include "MovePlayerState/RightMoveState.h"
//---------------------------------------------------------
RightMoveState::RightMoveState(StandPlayerState* standMoveState, JumpMoveState* jumpMoveState):m_currentState(nullptr),m_standMoveState(standMoveState),m_jumpMoveState(jumpMoveState)
{
	m_startPos = sf::Vector2f(160, 244);
}
//---------------------------------------------------------
void RightMoveState::movement(sf::Sprite& sprite, sf::Vector2i& pos, sf::Vector2f basePos , int& gravity, bool playerSide, b2Body* m_body) {

	if (playerSide) {
		m_keys = Keyboard(sf::Keyboard::Space, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Down);
	}
	else {
		m_keys = Keyboard(sf::Keyboard::Q, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, sf::Keyboard::S);
	}

	//moveWithRange(5,pos,playerSide);
	m_body->SetLinearVelocity(b2Vec2(10.f, m_body->GetLinearVelocity().y));
	movePlayer(m_startPos, 6, 10,sprite,pos, basePos);

	if (sf::Keyboard::isKeyPressed(m_keys.JUMP))
	{
		m_currentState = (BaseMovePlayerState*)m_jumpMoveState;
	}

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