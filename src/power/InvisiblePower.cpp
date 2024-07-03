#include "power/InvisiblePower.h"
#include "Resources.h"
#include "gameObject/Player.h"
#include "gameObject/Ball.h"

InvisiblePower::InvisiblePower(bool playerSide):m_playerSide(playerSide)
{

};

void InvisiblePower::activatePowerOnBall(Ball* ball)
{
    setPowerIsActive(true);

    // Adjust position if necessary
    b2Vec2 currentPosition = ball->getBody()->GetPosition();
    currentPosition.y -= 8.f; // Move the body 200 pixels higher (adjust as needed)
    ball->getBody()->SetTransform(currentPosition, ball->getBody()->GetAngle());    
    ball->getSprite().setColor(sf::Color(64, 64, 64, 64));
    // Set awake state to false to "pause" the body
    ball->getBody()->SetAwake(false);
}

void InvisiblePower::activatePowerOnPlayer(Player* player) {

    Box2d::getInstance().step();
    player->restartClock();
    player->setPowerOnPlayer(true);
    setPowerIsActive(false);
}

bool InvisiblePower::getSideOfPlayer()const {
    return m_playerSide;
}