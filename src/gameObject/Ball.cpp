#include "gameObject/Ball.h"
#include "Resources.h"
#include "Keyboard.h"
#include <iostream>
#include "power/RegularBehavior.h"

Ball::Ball():m_ballVelocity(5.0f, -10.0f), m_ball(25.0f), m_power(std::make_shared<RegularBehavior>())
{
	auto texture = &(Resources::getInstance().getBallTexture()[0]); 

    //----------------------box2d---------------------------//
    m_body = Box2d::getInstance().createBall(sf::Vector2f(900.f,100.f));
	

    m_sprite.setTexture(*texture);
    m_sprite.setOrigin(25.0f, 25.0f);
    m_ball.setTexture(texture);
   // m_ball.set
    m_ball.setOrigin(25.0f, 25.0f);
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
    // Update the position of the Box2D body
    b2Vec2 newPosition(position.x / SCALE, position.y / SCALE);
    m_body->SetTransform(newPosition, 0); // Set rotation to 0 degrees

    // Ensure no horizontal movement
    m_body->SetLinearVelocity(b2Vec2(0, m_body->GetLinearVelocity().y));

    update(); // Assuming this function updates the sprite position
    //m_sprite.setPosition(position); // Update the sprite position if needed
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

	window.draw(m_sprite);

    if (m_power->powerIsActive())
        m_power->draw(window, m_sprite.getPosition());
}



sf::Sprite & Ball::getSprite()
{
    //m_sprite.setOrigin(m_ball.getOrigin());
    //m_sprite.setPosition(m_ball.getPosition());

    return m_sprite;
}

void Ball::setBallVelocity(sf::Vector2f velocity)
{
    m_ballVelocity = velocity;
}



void Ball::setRegular()
{
    m_power = std::make_shared<RegularBehavior>();
}

void  Ball::move(sf::Vector2f pressed)
{

    if (m_power->powerIsActive())
    {
        m_power->checkTimeIsOver();
       
        if(m_power->stayInTheAir())
        {
            m_body->SetAwake(true);

            float side;
            (m_power->getSideOfPlayer()) ? side = -1.f : side = 1.f;

            // Set new velocity for the ball
            b2Vec2 newVelocity(50.f * side, m_body->GetLinearVelocity().y); // Assuming direction is a float

            m_body->SetLinearVelocity(newVelocity);
            //return;
        }
    }

    //if (m_clock.getElapsedTime().asSeconds() >= 1)
    //{
    //    m_clock.restart();
    //}

    update();

}

float Ball::getRadius() const {

    return m_ball.getRadius();
}

sf::CircleShape& Ball::getCircle() {

    return m_ball;
}


void Ball::setPower(std::shared_ptr<Power> power)
{
    m_power = power;
}


//-----------------------------------------------------------------------------
void Ball::update() {
    b2Vec2 position1 = m_body->GetPosition();
    m_sprite.setPosition(B2VecToSFVec(position1));
    m_sprite.setRotation(m_body->GetAngle() * 180.f / b2_pi);
}
//-----------------------------------------------------------------------------
void Ball::kick(bool rigthSide) {

    float kickForceX;  // Horizontal kick force
    float kickForceY = -400.2f;  // Vertical kick force (negative for upward)
    
    (rigthSide) ? kickForceX = -500.5f : kickForceX = 500.5f;
    b2Vec2 kickForce(kickForceX, kickForceY);
    m_body->ApplyForceToCenter(kickForce, true);

}
//-----------------------------------------------------------------------------
b2Body* Ball::getBody() {
    return m_body;
}
