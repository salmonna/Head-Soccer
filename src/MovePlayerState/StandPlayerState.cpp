#include"MovePlayerState/StandPlayerState.h"


//----------------------------------------------------------------------------------
StandPlayerState::StandPlayerState(LeftMoveState* leftMoveState, RightMoveState* rightMoveState)
	:m_leftMoveState(leftMoveState), m_rightMoveState(rightMoveState),m_nextState(nullptr)
{
	
}

//----------------------------------------------------------------------------------
void StandPlayerState::movement(sf::Sprite& sprite, sf::Vector2i& pos, sf::Vector2f basePos, int& gravity, bool playerSide) {

	if (playerSide) {
		m_keys = Keyboard(sf::Keyboard::Space, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Down);
	}
	else {
		m_keys = Keyboard(sf::Keyboard::Q, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, sf::Keyboard::S);
	}

	resetToPosition(sprite,pos,basePos);
	updateGravityAndCollision(sprite, basePos, pos, gravity);


	if (sf::Keyboard::isKeyPressed(m_keys.JUMP)) {//jump
		//m_nextState = 'J';
	}

	if (sf::Keyboard::isKeyPressed(m_keys.SPACE)) {//kick
		//m_nextState = 'S';
	}

	if (sf::Keyboard::isKeyPressed(m_keys.LEFT)) {//move left
		m_nextState = m_leftMoveState;
	}

	if (sf::Keyboard::isKeyPressed(m_keys.RIGHT)) {//move right
		m_nextState = m_rightMoveState;
	}
}
//----------------------------------------------------------------------------------
BaseMovePlayerState* StandPlayerState::handleMoveStatus() {
	BaseMovePlayerState* temp = m_nextState;

	if (m_nextState) {
		m_nextState = nullptr;
	}
	
	
	return temp;
}
//----------------------------------------------------------------------------------
StandPlayerState::~StandPlayerState()
{
}