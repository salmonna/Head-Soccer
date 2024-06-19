#include "gameObject/Ball.h"
#include "Resources.h"
#include "Keyboard.h"
#include <iostream>
#include "power/RegularBehavior.h"

Ball::Ball():m_ballVelocity(5.0f, -10.0f), m_ball(25.0f), m_moveBehavior(std::make_shared<RegularBehavior>())
{
	auto texture = &(Resources::getInstance().getBallTexture()[0]); 

	// הגדרת הכדור
    m_sprite.setTexture(*texture);
    m_ball.setTexture(texture);
   // m_ball.set
    m_ball.setOrigin(m_ball.getRadius(), m_ball.getRadius());
    m_ball.setPosition(900.0f, 988.0f); 
}


void Ball::restartBall()
{
    m_clock.restart();
}

void Ball::reset() {
    m_clock.restart();
}

sf::Clock & Ball::getClock()
{
    return m_clock;
}


bool Ball::m_registeritBall = MovingFactory::registeritMoving("Ball",
    []() -> std::shared_ptr<MovingObject> { return std::make_shared<Ball>(); });


void Ball::setPosition(sf::Vector2f position)
{
    m_ball.setPosition(position);
}

sf::Vector2f Ball::getVelocity() const
{
    return m_ballVelocity;

}

sf::Vector2f Ball::getPosition() const
{
    return m_sprite.getPosition();

}

void Ball::draw(sf::RenderWindow & window) const
{
	window.draw(m_ball);
}



sf::Sprite & Ball::getSprite()
{
    m_sprite.setOrigin(m_ball.getOrigin());
    m_sprite.setPosition(m_ball.getPosition());

    return m_sprite;
}

void Ball::setBallVelocity(sf::Vector2f velocity)
{
    m_ballVelocity = velocity;
}

void Ball::setTexture(sf::Texture& texture)
{
}


void  Ball::move(sf::Vector2f pressed)
{
   m_moveBehavior->performMove(this);
};

float Ball::getRadius() const {

    return m_ball.getRadius();
}

sf::CircleShape& Ball::getCircle() {

    return m_ball;
}

void Ball::setMoveBehavior(std::shared_ptr<MoveBehavior> moveBehavior)
{
    m_moveBehavior = moveBehavior;
}