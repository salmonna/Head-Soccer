#include "power/InvisiblePower.h"
#include "Resources.h"
#include "gameObject/Player.h"
#include "gameObject/Ball.h"
//--------------------------------------------------------------
InvisiblePower::InvisiblePower(bool PlayerSide):m_PlayerSide(PlayerSide)
{

};
//--------------------------------------------------------------
// Activates the invisible power on the ball
// This includes changing the ball's position, color, and awake state
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

//--------------------------------------------------------------
// Activates the invisible power on the player
void InvisiblePower::activatePowerOnPlayer(Player* player) {

    player->restartClock();
    player->setPowerOnPlayer(true);
    setPowerIsActive(false);
}
//--------------------------------------------------------------
// Returns the side of the player (true if player side, false otherwise)
bool InvisiblePower::getSideOfPlayer()const {
    return m_PlayerSide;
}