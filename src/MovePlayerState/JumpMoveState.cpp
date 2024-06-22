#include "MovePlayerState/JumpMoveState.h"

//----------------------------------------------------------------------------------
JumpMoveState::JumpMoveState(StandPlayerState* standState, KickMoveState* kickMoveState) :m_currentState(nullptr),
m_standMoveState(standState),m_kickMoveState(kickMoveState)
{
	m_startPos = sf::Vector2f(160, 8);
}

//----------------------------------------------------------------------------------
void JumpMoveState::movement(sf::Sprite& sprite, sf::Vector2i& pos, sf::Vector2f basePos, int& gravity, bool playerSide) {

	if (playerSide) {
		m_keys = Keyboard(sf::Keyboard::Space, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Down);
	}
	else {
		m_keys = Keyboard(sf::Keyboard::Q, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, sf::Keyboard::S);
	}

	if (pos.y > -180)
		pos.y -= 15;

	movePlayer(m_startPos, 7, 50, sprite, pos, basePos);
	updateGravityAndCollision(sprite, basePos, pos, gravity);

	if (sf::Keyboard::isKeyPressed(m_keys.LEFT)) {//move left

		moveWithRange(-5, pos, playerSide);
	}
	else if (sf::Keyboard::isKeyPressed(m_keys.RIGHT)) {//move right

		moveWithRange(5, pos, playerSide);
	}
	else if (sf::Keyboard::isKeyPressed(m_keys.SPACE)) {//move right

		m_currentState = m_kickMoveState;
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