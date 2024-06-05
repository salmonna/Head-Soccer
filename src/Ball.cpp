#include "Ball.h"
#include "Resources.h"

Ball::Ball():m_ballVelocity(200.0f, -300.0f)
{

	
	//get ball 1
	auto texture = Resources::getInstance().getBallTexture()[1];

	m_sprite.setTexture(texture);
	m_sprite.scale(0.5, 0.5);
	m_sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
	m_sprite.setPosition(900.0f, 988.0f);
}

void Ball::draw(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}


void  Ball::move(int keyPressed)
{

};