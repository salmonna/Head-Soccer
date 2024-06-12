#pragma once
#include "gameObject/MovingObject.h"
#include "Factory/MovingFactory.h"

class ComputerPlayer :public MovingObject 
{
public:
	ComputerPlayer();
	~ComputerPlayer();

	virtual void move(sf::Vector2f pressed) override{};
	virtual void draw(sf::RenderWindow& window)const override{};
	virtual sf::Vector2f getPosition() const { return sf::Vector2f(); };
	virtual sf::Sprite& getSprite() { return m_sprite; };

	void updateComputerPlayer(sf::RectangleShape& computer, sf::CircleShape& ball,
							  sf::RectangleShape& computerGoal, float deltaTime);

private:

	sf::Sprite m_sprite;
	sf::Vector2f m_velocity;

	static bool m_registeritComputerPlayer;
};

