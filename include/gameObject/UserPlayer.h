
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Keyboard.h"
#include "Factory/MovingFactory.h"
#include "power/Power.h"
#include <SFML/Audio.hpp>
#include "Box2d.h"
#include <iostream>
#include "MovePlayerState/BaseMovePlayerState.h"
#include "MovePlayerState/StandPlayerState.h"
#include "gameObject/Player.h"


class UserPlayer: public Player
{
public:
	UserPlayer(bool right, Keyboard keys);

	virtual void draw(sf::RenderWindow& window) const override;
	virtual void move() override;
	virtual sf::Sprite& getSprite() override;
	virtual void reset()override;
	virtual b2Body* getBody()const override;
	virtual void restartClock()override;
	void update();
	

	//----------------------- get --------------//
	virtual bool getSideOfPlayer()const override;
	virtual bool getAura() const override;
	Keyboard getKey() const;
	virtual std::shared_ptr<Power> getPower() const override;
	virtual bool getPowerOnPlayer() const override;
	
	//----------------------- set --------------//
	virtual void setPowerOnPlayer(bool powerOnPlayer)override;
	virtual void setAura(bool aura)override;
	
	virtual ~UserPlayer();
private:

	void resetPlayerProgress();

	sf::Sprite m_sprite;
	sf::Clock m_powerClock;
	sf::Vector2f m_basePosition;
	sf::Color m_PlayerColor;
	sf::Sound m_auraSound;
	Keyboard m_keys;

	LeftMoveState m_leftMoveState;
	RightMoveState m_rightMoveState;
	JumpMoveState m_jumpMoveState;
	KickMoveState m_kickMoveState;
	StandPlayerState m_standMoveState;
	BaseMovePlayerState* m_currentMoveState;

	std::shared_ptr<Power> m_power;

	b2Body* m_body;

	bool m_PlayerSide;
	bool m_aura;
	bool m_powerOnPlayer;

	static bool m_registeritRightPlayer;
	static bool m_registeritLeftPlayer;
};