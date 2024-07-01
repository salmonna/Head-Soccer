
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
	virtual sf::Sprite& getSprite() override;
	virtual void reset()override;
	virtual b2Body* getBody()override;
	Keyboard getKey() const;
  
	void setPowerOnPlayer(bool powerOnPlayer);
	bool getPowerOnPlayer() const;

	void resetProgress();

	std::shared_ptr<Power> getPower();

	void setAura(bool aura);
	bool getAura() const;
	bool getSide() const;
	void update();
	
	bool getSideOfPlayer();
	void restartClock();

	virtual ~Player() {
		std::cout << " P-D" << std::endl;
		m_body->DestroyFixture(m_body->GetFixtureList());
		auto world = Box2d::getInstance().getBox2dWorld();
		world->DestroyBody(m_body);
		m_body = nullptr;
	};

private:

	int m_numOfJump;
	int m_posX;
	int m_posY;
	int m_move;
	int m_gravity;
	bool m_playerSide;
	bool m_aura;
	bool m_powerOnPlayer;

	std::shared_ptr<Power> m_power;

	sf::Sprite m_sprite;
	sf::Clock m_powerClock;
	sf::Clock m_powerClock2;
	std::vector<sf::Vector2f> m_startSprite;
	sf::Vector2f m_basePosition;

	Keyboard m_keys;
	sf::Sound m_sound;
  
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


