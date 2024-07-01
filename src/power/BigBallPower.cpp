#include "power/BigBallPower.h"
#include "gameObject/Ball.h"
#include "Resources.h"
#include "gameObject/Player.h"


BigBallPower::BigBallPower(bool playerSide):m_playerSide(playerSide)
{


};

void BigBallPower::activatePowerOnBall(b2Body* ballBody)
{
    setPowerIsActive(true);

    // Adjust position if necessary
    b2Vec2 currentPosition = ballBody->GetPosition();
    currentPosition.y -= 8.f; // Move the body 200 pixels higher (adjust as needed)

    ballBody->SetTransform(currentPosition, ballBody->GetAngle());

    // Update the density
    //b2MassData massData;
    //ballBody->GetFixtureList()->GetShape()->ComputeMass(&massData, 80.0f); // Adjust density as needed
    //ballBody->SetMassData(&massData);

    // Set awake state to false to "pause" the body
    ballBody->SetAwake(false);
}

void BigBallPower::activatePowerOnPlayer(Player* player) {


    /*playerBody->ApplyLinearImpulseToCenter(b2Vec2(0.f, -1000.f), true);*/
    //player->getSprite().setColor(sf::Color(128, 128, 128));
    player->getSprite().setColor(sf::Color(256, 256, 256));
    //player->getBody()->SetAwake(false);
    player->restartClock();
    player->setPowerOnPlayer(true);
    setPowerIsActive(false);
}