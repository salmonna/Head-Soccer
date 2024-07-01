#include "power/BigBallPower.h"
#include "gameObject/Ball.h"
#include "Resources.h"
#include "gameObject/Player.h"


BigBallPower::BigBallPower(bool playerSide):m_playerSide(playerSide)
{

};

void BigBallPower::activatePowerOnBall(Ball* ball)
{
    setPowerIsActive(true);

    // Adjust position if necessary
    b2Vec2 currentPosition = ball->getBody()->GetPosition();
    currentPosition.y -= 5.f; // Move the body 200 pixels higher (adjust as needed)
    ball->getBody()->SetTransform(currentPosition, ball->getBody()->GetAngle());

    // Update the density
    b2MassData massData;
    ball->getBody()->GetFixtureList()->GetShape()->ComputeMass(&massData, 50.0f); // Adjust density as needed
    ball->getBody()->SetMassData(&massData);
    

    // Set awake state to false to "pause" the body
    ball->getBody()->SetAwake(false);
}

void BigBallPower::activatePowerOnPlayer(Player* player) {

    player->restartClock();
    player->setPowerOnPlayer(true);
    setPowerIsActive(false);
}

bool BigBallPower::getSideOfPlayer()const {
    return m_playerSide;
}