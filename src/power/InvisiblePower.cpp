#include "power/InvisiblePower.h"
#include "Resources.h"
#include "gameObject/Player.h"
#include "gameObject/Ball.h"

InvisiblePower::InvisiblePower(bool PlayerSide):m_PlayerSide(PlayerSide)
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

void InvisiblePower::activatePowerOnPlayer(Player* Player) {


    Player->restartClock();
    Player->setPowerOnPlayer(true);
    setPowerIsActive(false);
}

bool InvisiblePower::getSideOfPlayer()const {
    return m_PlayerSide;
}