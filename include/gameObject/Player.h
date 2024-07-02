
#pragma once
#include "MovingObject.h"
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


class Player: public MovingObject
{
public:
	Player(bool right, Keyboard keys);

	virtual void draw(sf::RenderWindow& window) const override;
	virtual void move() override;
	virtual sf::Sprite& getSprite() override;
	virtual void reset()override;
	virtual b2Body* getBody()const override;
	
	void update();
	void restartClock();

	//----------------------- get --------------//
	bool getSideOfPlayer()const;
	bool getAura() const;
	Keyboard getKey() const;
	std::shared_ptr<Power> getPower() const;
	bool getPowerOnPlayer() const;
	
	//----------------------- set --------------//
	void setPowerOnPlayer(bool powerOnPlayer);
	void setAura(bool aura);
	
	virtual ~Player();
private:

	void resetToPosition(sf::Vector2f startPos = sf::Vector2f(160, 590));
	void deactivatePower();
	void resetPlayerProgress();

	sf::Sprite m_sprite;
	sf::Clock m_powerClock;
	sf::Vector2f m_basePosition;
	sf::Color m_playerColor;
	sf::Sound m_sound;

	Keyboard m_keys;

	LeftMoveState m_leftMoveState;
	RightMoveState m_rightMoveState;
	JumpMoveState m_jumpMoveState;
	KickMoveState m_kickMoveState;
	StandPlayerState m_standMoveState;
	BaseMovePlayerState* m_currentMoveState;

	std::shared_ptr<Power> m_power;

	b2Body* m_body;

	bool m_playerSide;
	bool m_aura;
	bool m_powerOnPlayer;

	static bool m_registeritRightPlayer;
	static bool m_registeritLeftPlayer;
};