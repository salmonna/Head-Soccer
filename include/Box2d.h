

#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

const float SCALE = 30.f;  // Scale factor for converting Box2D units to SFML pixels
const float GRAVITY = 1.f;
const float JUMP_FORCE = 50.7f;
const float PLAYER_GRAVITY_SCALE = 0.5f;  // Gravity scale for the player

class Box2d
{
public:

	static Box2d& getInstance() {
		static Box2d instance;
		return instance;
	}
	void draw(sf::RenderWindow& window)const;
	b2World* getBox2dWorld();

private:	
	Box2d(const Box2d&) = default;
	Box2d& operator=(const Box2d&) = delete;
	Box2d();
	~Box2d();
	b2World m_world;
	sf::RectangleShape m_ground;
	sf::RectangleShape m_ceiling;
	sf::RectangleShape m_leftWall;
	sf::RectangleShape m_rightWall;
};

