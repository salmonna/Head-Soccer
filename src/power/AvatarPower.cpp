#include "power\AvatarPower.h"
#include "gameObject/Ball.h"
#include "gameObject/Player.h"
#include "Resources.h"

//---------------------------------------------------------------------------
AvatarPower::AvatarPower(bool PlayerSide) :m_spriteSheetClock(), m_index(0),
m_PlayerSide(PlayerSide)
{
    m_sprite.setTexture(Resources::getInstance().getPowerTexture()[6]);

    int height = 220;

    for (int i = 0; i < 5; i++)
    {
        m_spriteSheet.push_back(std::pair(sf::Vector2i(0, i* height), sf::Vector2i(306, height)));
        m_spriteSheet.push_back(std::pair(sf::Vector2i(306, i* height), sf::Vector2i(306, height)));
    }

    try
    {
        m_sprite.setTextureRect(sf::IntRect(m_spriteSheet[0].first, m_spriteSheet[0].second));

    }
    catch (const std::exception&)
    {
        throw FileException("Deviation from the array");
    }
};
//---------------------------------------------------------------------------
// Activates the power on a ball, adjusting its position and sleep state.
void AvatarPower::activatePowerOnBall(Ball* ball)
{
    setPowerIsActive(true);

    float side;
    (m_PlayerSide) ? side = -1.f : side = 1.f;
   
    // Adjust position if necessary
    b2Vec2 currentPosition = ball->getBody()->GetPosition();
    currentPosition.x += 4.f* side; // Move the body
    ball->getBody()->SetTransform(currentPosition, ball->getBody()->GetAngle());


    // Set awake state to false to "pause" the body
    ball->getBody()->SetAwake(false);
}
//---------------------------------------------------------------------------
// Activates the power on a player, applying an impulse and setting state variables.
void AvatarPower::activatePowerOnPlayer(Player* player) {

    player->getBody()->ApplyLinearImpulseToCenter(b2Vec2(0.f, -1500.f), true);
    player->restartClock();
    player->setPowerOnPlayer(true);
    setPowerIsActive(false);
}
//---------------------------------------------------------------------------
// Draws the AvatarPower sprite onto the given render window.
void AvatarPower::draw(sf::RenderWindow& window) const
{
    window.draw(m_sprite);
}
//---------------------------------------------------------------------------
// Updates the animation frame of the AvatarPower sprite based on elapsed time.
void AvatarPower::animation(sf::Vector2f position)
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

    position.x -= 306.f / 2.f;
    position.y -= 177.f * 0.8f;

    m_sprite.setPosition(position);


}
//---------------------------------------------------------------------------
// Retrieves the side of the player associated with the AvatarPower.
bool AvatarPower::getSideOfPlayer()const {
    return m_PlayerSide;
}
