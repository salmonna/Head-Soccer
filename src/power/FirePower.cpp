#include "power/FirePower.h"
#include "gameObject/Ball.h"
#include "Resources.h"


FirePower::FirePower() :m_ballVelocity(), m_clock()
{



};

void FirePower::activatePower(sf::CircleShape& ball, sf::Vector2f& currVelocity, sf::Vector2f & direction)
{
    currVelocity = sf::Vector2f(1500.f, 0.f);
    currVelocity.x *= direction.x;

    sf::Vector2f currPos = ball.getPosition();
    currPos.y -= 300.f;
    ball.setPosition(currPos);

    ball.setTexture(&Resources::getInstance().getBallTexture()[2]);
}


