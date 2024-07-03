#include "power/FistPower.h"
#include "gameObject/Ball.h"
#include "Resources.h"
#include "gameObject/Player.h"


FistPower::FistPower(bool playerSide):m_playerSide(playerSide)
{

    try
    {
        m_sprite.setTexture(Resources::getInstance().getPowerTexture()[7]);

        if (!m_playerSide)
        {
            m_sprite.scale(-1.f, 1.f);
        }

    }
    catch (const std::exception& e)
    {
        throw FileException("Deviation from the array in BigBallPower");
    }    

};

void FistPower::activatePowerOnBall(Ball* ball)
{
    setPowerIsActive(true);

    // Adjust position if necessary
    b2Vec2 currentPosition = ball->getBody()->GetPosition();
    float side;
    (m_playerSide) ? side = -3.5f : side = 3.5f;
    currentPosition.x += side; // Move the body 200 pixels higher (adjust as needed)
    ball->getBody()->SetTransform(currentPosition, ball->getBody()->GetAngle());

    // Update the density
    b2MassData massData;
    ball->getBody()->GetFixtureList()->GetShape()->ComputeMass(&massData, 10000.0f); // Adjust density as needed
    ball->getBody()->SetMassData(&massData);
    
    // Set awake state to false to "pause" the body
    ball->getBody()->SetAwake(false);
}

//--------------------------------------------------------------
void FistPower::draw(sf::RenderWindow& window) const {
    window.draw(m_sprite);
}

void FistPower::animation(sf::Vector2f position)
{
    if (!m_playerSide)
    {
        position.y -= m_sprite.getGlobalBounds().height / 2;
        position.x += m_sprite.getGlobalBounds().width / 2;
    }
    else
    {
        position.y -= m_sprite.getGlobalBounds().height / 2;
        position.x -= m_sprite.getGlobalBounds().width / 2;
    }

    m_sprite.setPosition(position);
}

void FistPower::activatePowerOnPlayer(Player* player) {

    Box2d::getInstance().step();
    setPowerIsActive(false);
}

bool FistPower::getSideOfPlayer()const {
    return m_playerSide;
}