#include "gameObject/Ball.h"
#include "Resources.h"
#include "Keyboard.h"
#include <iostream>

Ball::Ball():m_ballVelocity(5.0f, -10.0f), m_ball(25.0f)
{
	auto texture = &(Resources::getInstance().getBallTexture()[0]); 

    //----------------------box2d---------------------------//
    auto world = Box2d::getInstance().getBox2dWorld();
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(900.f / SCALE, 100.f / SCALE);
    m_body = world->CreateBody(&bodyDef);

    b2CircleShape circle;
    circle.m_radius = 25.0f / SCALE;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circle;
    fixtureDef.density = 0.4f;
    fixtureDef.restitution = 0.8f;
    m_body->CreateFixture(&fixtureDef);
	

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
    //m_clock.restart();
}

bool Ball::m_registeritBall = MovingFactory::registeritMoving("Ball",
    []() -> std::shared_ptr<MovingObject> { return std::make_shared<Ball>(); });


void Ball::setPosition(sf::Vector2f position)
{
    // Update the position of the Box2D body
    b2Vec2 newPosition(position.x / SCALE, position.y / SCALE);
    //m_ball.setPosition(position);
    m_body->SetTransform(newPosition, m_body->GetAngle());
    update();
    //m_sprite.setPosition(position);
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



void  Ball::move(sf::Vector2f pressed)
{
    update();

};

float Ball::getRadius() const {

    return m_ball.getRadius();
}

sf::CircleShape& Ball::getCircle() {

    return m_ball;
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