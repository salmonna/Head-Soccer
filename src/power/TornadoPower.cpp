#include "power/TornadoPower.h"
#include "gameObject/Ball.h"
#include "Resources.h"
#include "gameObject/Player.h"
//----------------------------------------------------------------------------
TornadoPower::TornadoPower(bool PlayerSide) :m_spriteSheetClock(), m_index(0), m_PlayerSide(PlayerSide)
{
    m_sprite.setTexture(Resources::getInstance().getPowerTexture()[3]);


    m_spriteSheet.push_back(std::pair(sf::Vector2i(0, 0), sf::Vector2i(334, 317)));
    m_spriteSheet.push_back(std::pair(sf::Vector2i(327, 0), sf::Vector2i(334, 317)));
    m_spriteSheet.push_back(std::pair(sf::Vector2i(654, 0), sf::Vector2i(334, 317)));
    m_spriteSheet.push_back(std::pair(sf::Vector2i(0, 317), sf::Vector2i(334, 317)));
    m_spriteSheet.push_back(std::pair(sf::Vector2i(327, 317), sf::Vector2i(334, 317)));
    m_spriteSheet.push_back(std::pair(sf::Vector2i(654, 317), sf::Vector2i(334, 317)));
    m_spriteSheet.push_back(std::pair(sf::Vector2i(0, 634), sf::Vector2i(334, 317)));
    m_spriteSheet.push_back(std::pair(sf::Vector2i(327, 634), sf::Vector2i(334, 317)));
    m_spriteSheet.push_back(std::pair(sf::Vector2i(654, 634), sf::Vector2i(334, 317)));


    try
    {
        m_sprite.setTextureRect(sf::IntRect(m_spriteSheet[0].first, m_spriteSheet[0].second));

    }
    catch (const std::exception&)
    {
        throw FileException("Deviation from the array");
    }

};
//----------------------------------------------------------------------------
// Activates the tornado power on the ball
// This includes changing the ball's position and awake state
void TornadoPower::activatePowerOnBall(Ball* ball)
{
    setPowerIsActive(true);

    // Adjust position if necessary
    b2Vec2 currentPosition = ball->getBody()->GetPosition();
    float side;
    (m_PlayerSide) ? side = -1.f : side = 1.f;
    currentPosition.x += side; // Move the body 200 pixels higher (adjust as needed)
    ball->getBody()->SetTransform(currentPosition, ball->getBody()->GetAngle());

    // Set awake state to false to "pause" the body
    ball->getBody()->SetAwake(false);
}

//----------------------------------------------------------------------------
// Activates the tornado power on the player
void TornadoPower::activatePowerOnPlayer(Player* player) {


    player->getBody()->ApplyLinearImpulseToCenter(b2Vec2(0.f, -1500.f), true);
    player->restartClock();
    player->setPowerOnPlayer(true);
    setPowerIsActive(false);
}

//----------------------------------------------------------------------------
// Draws the tornado sprite to the window
void TornadoPower::draw(sf::RenderWindow& window) const
{
    window.draw(m_sprite);
}
//----------------------------------------------------------------------------
// Manages the animation of the tornado power
void TornadoPower::animation(sf::Vector2f position)
{

    if (m_index == m_spriteSheet.size())
    {
        m_index = 0;
    }

    if (m_spriteSheetClock.getElapsedTime().asMilliseconds() >= 250.f)
    {
        m_sprite.setTextureRect(sf::IntRect(m_spriteSheet[m_index].first, m_spriteSheet[m_index].second));
        m_index++;
        m_spriteSheetClock.restart();
    }

    position.x -= 334.f / 2.f;
    position.y -= 317.f * 0.9f;

    m_sprite.setPosition(position);
}

//----------------------------------------------------------------------------
// Returns the side of the player (true if player side, false otherwise)
bool TornadoPower::getSideOfPlayer()const {
    return m_PlayerSide;
}