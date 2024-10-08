#include "gameObject/Ball.h"
#include "Resources.h"
#include "Keyboard.h"
#include "power/AvatarPower.h"
#include <iostream>
//-----------------------------------------------------------------------------
// Constructor initializes member variables
Ball::Ball():m_basePosition(900.0f, 100.0f), m_restartBall(false),m_body(nullptr)
{
	auto texture = &(Resources::getInstance().getBallTexture()[0]); 

    //----------------------box2d---------------------------//
    m_body = Box2d::getInstance().createBall(sf::Vector2f(900.f,100.f));
    m_power = std::make_shared<AvatarPower>(true);
    m_body->GetMassData(&m_bodyMass);
    m_sprite.setTexture(*texture);
    m_sprite.setOrigin(25.0f, 25.0f);
    m_ballColor = m_sprite.getColor();
    m_gravityScale = m_body->GetGravityScale();
}


bool Ball::m_registeritBall = MovingFactory::registeritMoving("Ball",
    []() -> std::shared_ptr<MovingObject> { return std::make_shared<Ball>(); });

//-----------------------------------------------------------------------------
// Move function for updating ball state
void  Ball::move()
{

    if (m_power->powerIsActive())
        updatePowerState();
    else if (m_restartBall)
    {
        m_body->SetGravityScale(m_gravityScale);
        m_body->SetMassData(&m_bodyMass);
        m_sprite.setColor(m_ballColor);
        m_restartBall = false;
    }

    update();
}
//-----------------------------------------------------------------------------
// Draw function to render ball 
void Ball::draw(sf::RenderWindow & window) const
{

	window.draw(m_sprite);

    if (m_power->powerIsActive())
        m_power->draw(window);
}
//-----------------------------------------------------------------------------
// Update function to sync Box2D body position and sprite position
void Ball::update() {
    b2Vec2 position1 = m_body->GetPosition();
    m_sprite.setPosition(B2VecToSFVec(position1));
    m_sprite.setRotation(m_body->GetAngle() * 180.f / b2_pi);

    m_power->animation(m_sprite.getPosition());
}
//-----------------------------------------------------------------------------
// Update power state function to handle active powers
void Ball::updatePowerState() {
    m_power->checkTimeIsOver();

    if (m_power->stayInTheAir()) {
        m_body->SetAwake(true);

        float side = (m_power->getSideOfPlayer()) ? -1.f : 1.f;

        // Set new velocity for the ball
        b2Vec2 newVelocity(50.f * side, m_body->GetLinearVelocity().y); // Assuming direction is a float
        m_body->SetLinearVelocity(newVelocity);
    }
    else {
        m_restartBall = true;
    }
}
//-----------------------------------------------------------------------------
// Kick function to apply force to the ball
void Ball::kick(bool rigthSide) {

    float kickForceX;  // Horizontal kick force
    float kickForceY = -400.2f;  // Vertical kick force (negative for upward)
    
    (rigthSide) ? kickForceX = -500.5f : kickForceX = 500.5f;
    b2Vec2 kickForce(kickForceX, kickForceY);
    m_body->ApplyForceToCenter(kickForce, true);
}
//-----------------------------------------------------------------------------
// Reset function to reset ball position and velocity
void Ball::reset() {
    // Update the position of the Box2D body
    b2Vec2 newPosition(m_basePosition.x / SCALE, m_basePosition.y / SCALE);
    m_body->SetTransform(newPosition, m_body->GetAngle());

    // Reset the velocity of the Box2D body
    m_body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));  // Set linear velocity to zero
    m_body->SetAngularVelocity(0.0f);               // Set angular velocity to zero

    update();
}
//-----------------------------------------------------------------------------
// Getter function for retrieving the Box2D body
b2Body* Ball::getBody() const {
    return m_body;
}
//-----------------------------------------------------------------------------
// Getter function for retrieving the ball power
std::shared_ptr<Power> Ball::getPower()const
{
    return m_power;
}
//-----------------------------------------------------------------------------
// Getter function for retrieving the ball color
sf::Color Ball::getBallColor()const {
    return m_ballColor;
}
//-----------------------------------------------------------------------------
// Getter function for retrieving the ball sprite
sf::Sprite & Ball::getSprite()
{
    return m_sprite;
}
//-----------------------------------------------------------------------------
// Getter function for retrieving the ball mass data
b2MassData Ball::getBallMass() const{
    return m_bodyMass;
}
//-----------------------------------------------------------------------------
// Function to set the position of the ball
void Ball::setPosition(sf::Vector2f position)
{
    // Update the position of the Box2D body
    b2Vec2 newPosition(position.x / SCALE, position.y / SCALE);
    m_body->SetTransform(newPosition, 0); // Set rotation to 0 degrees

    // Ensure no horizontal movement
    m_body->SetLinearVelocity(b2Vec2(0, m_body->GetLinearVelocity().y));
    update(); // Assuming this function updates the sprite position
}
//-----------------------------------------------------------------------------
// Setter function to set the ball power
void Ball::setPower(std::shared_ptr<Power> power)
{
    m_power = power;
}
//-----------------------------------------------------------------------------
// Destructor to clean up Box2D body and fixtures
Ball::~Ball(){
    m_body->DestroyFixture(m_body->GetFixtureList());
    auto world = Box2d::getInstance().getBox2dWorld();
    world->DestroyBody(m_body);
    m_body = nullptr;
}