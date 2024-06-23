
#pragma once
#include "MovingObject.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "Keyboard.h"
#include "Factory/MovingFactory.h"
#include "power/Power.h"
#include "Box2d.h"
//-------
#include "MovePlayerState/BaseMovePlayerState.h"
#include "MovePlayerState/StandPlayerState.h"
//-------

class Player: public MovingObject
{
public:
	Player(bool right, Keyboard keys);

	virtual void draw(sf::RenderWindow& window) const override;
	virtual void move(sf::Vector2f pressed) override;

	virtual  sf::Vector2f getPosition() const override;
	virtual sf::Sprite& getSprite() override;
	virtual void reset()override;
	Keyboard getKey() const;
  
	void resetProgress();
	void activatePower(sf::Sprite& ball, sf::Sprite& player);

	void setAura(bool aura);
	bool getAura() const;
	void update();
	bool getSideOfPlayer();

	virtual ~Player() = default;
private:

	int m_numOfJump;
	int m_posX;
	int m_posY;
	int m_move;
	int m_gravity;
	bool m_playerSide;
	bool m_aura;

	std::unique_ptr<Power> m_power;

	sf::Sprite m_sprite;
	sf::Clock m_moveClock;
	std::vector<sf::Vector2f> m_startSprite;
	sf::Vector2f m_basePosition;

	Keyboard m_keys;
  
	static bool m_registeritRightPlayer;
	static bool m_registeritLeftPlayer;
  
	void resetToPosition(sf::Vector2f startPos = sf::Vector2f(160, 590), int numOfJump = 0, int posX = 0, int posY = 0);

	LeftMoveState m_leftMoveState;
	RightMoveState m_rightMoveState;
	JumpMoveState m_jumpMoveState;
	KickMoveState m_kickMoveState;
	StandPlayerState m_standMoveState;

	BaseMovePlayerState* m_currentMoveState;

	b2Body* m_body;

};


