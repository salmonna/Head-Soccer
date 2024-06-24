#include"MovePlayerState/StandPlayerState.h"
#include <iostream>

//----------------------------------------------------------------------------------
StandPlayerState::StandPlayerState(LeftMoveState* leftMoveState, RightMoveState* rightMoveState, JumpMoveState* jumeMoveState, KickMoveState* kickMoveState)
	:m_leftMoveState(leftMoveState), m_rightMoveState(rightMoveState),m_jumpMoveState(jumeMoveState),m_kickMoveState(kickMoveState), m_nextState(nullptr)
{
	
}

//----------------------------------------------------------------------------------
void StandPlayerState::movement(sf::Sprite& sprite, sf::Vector2i& pos, sf::Vector2f basePos, int& gravity, bool playerSide, b2Body* m_body) {

	setKeyboard(playerSide);
	
	resetToPosition(sprite,pos,basePos);
	m_body->SetLinearVelocity(b2Vec2(0.f, m_body->GetLinearVelocity().y));

	if (sf::Keyboard::isKeyPressed(m_keys.JUMP)) {//jump
		m_nextState = m_jumpMoveState;
	}
	else if (sf::Keyboard::isKeyPressed(m_keys.SPACE)) {//kick

		m_nextState = m_kickMoveState;
	}
	else if (sf::Keyboard::isKeyPressed(m_keys.LEFT)) {//move left

		m_nextState = m_leftMoveState;
	}
	else if (sf::Keyboard::isKeyPressed(m_keys.RIGHT)) {//move right

		m_nextState = m_rightMoveState;
	}
	else {
		m_body->SetLinearVelocity(b2Vec2(0.f, m_body->GetLinearVelocity().y));  // Stop horizontal movement when no key is pressed
	}

}
//----------------------------------------------------------------------------------
BaseMovePlayerState* StandPlayerState::handleMoveStatus() {
	
	BaseMovePlayerState* temp = m_nextState;
	m_nextState = nullptr;
	return temp;
}
//----------------------------------------------------------------------------------
void StandPlayerState::setKeyboard(bool playerSide) {

	if (playerSide) {
		m_keys = Keyboard(sf::Keyboard::Space, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Down);
	}
	else {
		m_keys = Keyboard(sf::Keyboard::Q, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, sf::Keyboard::S);
	}
}
//----------------------------------------------------------------------------------
StandPlayerState::~StandPlayerState()
{
}