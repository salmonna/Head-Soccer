#include "power/InvisiblePower.h"
#include "Resources.h"

InvisiblePower::InvisiblePower() 
{



};

void InvisiblePower::activatePower(sf::CircleShape& ball, sf::Vector2f& currVelocity, sf::Vector2f& direction)
{
    currVelocity = sf::Vector2f(1500.f, 0.f);
    currVelocity.x *= direction.x;

    sf::Vector2f currPos = ball.getPosition();
    currPos.y -= 300.f;
    ball.setPosition(currPos);

    ball.setFillColor(sf::Color(256, 256, 256, 16));
}