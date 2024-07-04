#pragma once
#include <SFML/Graphics.hpp>
#include "Factory/MovingFactory.h"
#include "power/Power.h"
#include "gameObject/Ball.h"
#include "Box2d.h"
#include <iostream>
#include "gameObject/Player.h"
#include <SFML/Audio.hpp>

class ComputerPlayer :public Player
{
public:

	ComputerPlayer(std::shared_ptr<Ball>& ball);
	
	virtual void move() override;
	virtual void draw(sf::RenderWindow& window)const override;
	virtual sf::Sprite& getSprite() override { return m_sprite; };
	virtual void reset()override;
	virtual b2Body* getBody()const override;

	void movePlayer(sf::Vector2f startPos, int maxSprite, float maxTime);

	virtual bool getAura() const override;
	virtual void setAura(bool aura) override;
	virtual bool getSideOfPlayer()const override;
	virtual void setPowerOnPlayer(bool powerOnPlayer) override;
	virtual bool getPowerOnPlayer() const override;
	virtual std::shared_ptr<Power> getPower() const override;
	virtual void restartClock()override;

	virtual ~ComputerPlayer();

private:

	
	void checkIfTurnOnAura();
	void update();
	void updateMovement(const sf::Vector2f ballPosition, float length);
	
	std::shared_ptr<Ball> m_ball;
	std::shared_ptr<Power> m_power;
	std::vector<sf::Vector2f> m_startSprite;

	sf::Clock m_moveClock;
	sf::Clock m_powerClock;
	sf::Vector2f m_basePosition;
	sf::Vector2f m_velocity;
	sf::Sprite m_sprite;
	sf::Color m_PlayerColor;
	b2Body* m_body;

	bool m_jump;
	bool m_aura;
	bool m_powerOnPlayer;
	int m_numOfJump;

	sf::Sound m_auraSound;
	static bool m_registeritComputerPlayer;
};

