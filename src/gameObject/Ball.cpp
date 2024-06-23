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
    bodyDef.position.Set(425.f / SCALE, 100.f / SCALE);
    m_body = world->CreateBody(&bodyDef);

    b2CircleShape circle;
    circle.m_radius = 25.0f / SCALE;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circle;
    fixtureDef.density = 0.8f;
    fixtureDef.restitution = 0.6f;
    m_body->CreateFixture(&fixtureDef);
	

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
    //m_clock.restart();
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



void  Ball::move(sf::Vector2f pressed)
{
    update();
    //if (m_clock.getElapsedTime().asSeconds() >= 1)
    //{
    //    m_clock.restart();
    //}

    //float deltaTime = m_clock.restart().asSeconds();

    //const float gravity = 980.0f;  // כוח המשיכה בפיקסלים לשנייה בריבוע
    //const float restitution = 0.8f;  // מקדם ההתנגשות

    //// עדכון המהירות בעקבות כוח המשיכה
    //m_ballVelocity.y += gravity * deltaTime;

    //// עדכון מיקום הכדור
    //m_ball.move(m_ballVelocity * deltaTime);


    //// בדיקת התנגשות עם הקרקע
    //if (m_ball.getPosition().y + m_ball.getRadius() >= 835.0f) {
    //    m_ball.setPosition(m_ball.getPosition().x, 835.0f - m_ball.getRadius());
    //    m_ballVelocity.y = -m_ballVelocity.y * restitution;
    //}

    //// בדיקת התנגשות עם הקירות והחלון
    //sf::FloatRect ballBounds = m_ball.getGlobalBounds();
    //sf::FloatRect windowBounds(0.0f, 0.0f, 1800.0f, 835.0f);


    //if (ballBounds.left < windowBounds.left) {
    //    m_ball.setPosition(windowBounds.left + m_ball.getRadius(), m_ball.getPosition().y);
    //    m_ballVelocity.x = -m_ballVelocity.x * restitution;
    //}
    //else if (ballBounds.left + ballBounds.width > windowBounds.left + windowBounds.width) {
    //    m_ball.setPosition(windowBounds.left + windowBounds.width - m_ball.getRadius(), m_ball.getPosition().y);
    //    m_ballVelocity.x = -m_ballVelocity.x * restitution;
    //}
    //if (ballBounds.top < windowBounds.top) {
    //    m_ball.setPosition(m_ball.getPosition().x, windowBounds.top + m_ball.getRadius());
    //    m_ballVelocity.y = -m_ballVelocity.y * restitution;
    //}
    //else if (ballBounds.top + ballBounds.height > windowBounds.top + windowBounds.height) {
    //    m_ball.setPosition(m_ball.getPosition().x, windowBounds.top + windowBounds.height - m_ball.getRadius());
    //    m_ballVelocity.y = -m_ballVelocity.y * restitution;
    //}
    

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