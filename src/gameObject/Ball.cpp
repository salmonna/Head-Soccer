#include "gameObject/Ball.h"
#include "Resources.h"
#include "Keyboard.h"
#include <iostream>
#include "power/RegularBehavior.h"

Ball::Ball():m_power(std::make_shared<RegularBehavior>()), m_basePosition(900.0f, 100.0f)
{
	auto texture = &(Resources::getInstance().getBallTexture()[0]); 

    //----------------------box2d---------------------------//
    m_body = Box2d::getInstance().createBall(sf::Vector2f(900.f,100.f));
	
    m_sprite.setTexture(*texture);
    m_sprite.setOrigin(25.0f, 25.0f);
}


bool Ball::m_registeritBall = MovingFactory::registeritMoving("Ball",
    []() -> std::shared_ptr<MovingObject> { return std::make_shared<Ball>(); });

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
        }
    }

    update();

}

void Ball::draw(sf::RenderWindow & window) const
{
	window.draw(m_sprite);

    if (m_power->powerIsActive())
        m_power->draw(window, m_sprite.getPosition());
}

void Ball::setPosition(sf::Vector2f position)
{
    // Update the position of the Box2D body
    b2Vec2 newPosition(position.x / SCALE, position.y / SCALE);
    m_body->SetTransform(newPosition, 0); // Set rotation to 0 degrees

    // Ensure no horizontal movement
    m_body->SetLinearVelocity(b2Vec2(0, m_body->GetLinearVelocity().y));
    update(); // Assuming this function updates the sprite position
}

sf::Sprite & Ball::getSprite()
{
    return m_sprite;
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
//-----------------------------------------------------------------------------
std::shared_ptr<Power> Ball::getPower()
{
    return m_power;
}
//-----------------------------------------------------------------------------
void Ball::reset() {
    // Update the position of the Box2D body
    b2Vec2 newPosition(m_basePosition.x / SCALE, m_basePosition.y / SCALE);
    m_body->SetTransform(newPosition, m_body->GetAngle());

    // Reset the velocity of the Box2D body
    m_body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));  // Set linear velocity to zero
    m_body->SetAngularVelocity(0.0f);               // Set angular velocity to zero

    update();
}