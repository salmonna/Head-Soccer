#include "power\AvatarPower.h"
#include "gameObject/Ball.h"
#include "gameObject/Player.h"
#include "Resources.h"


AvatarPower::AvatarPower(bool PlayerSide) :m_spriteSheetClock(), m_index(0),
m_PlayerSide(PlayerSide)
{
    m_sprite.setTexture(Resources::getInstance().getPowerTexture()[6]);

    float height = 220.f;

    for (int i = 0; i < 5; i++)
    {
        m_spriteSheet.push_back(std::pair(sf::Vector2i(0, i* height), sf::Vector2i(306.f, height)));
        m_spriteSheet.push_back(std::pair(sf::Vector2i(306.f, i* height), sf::Vector2i(306.f, height)));
    }

    try
    {
        m_sprite.setTextureRect(sf::IntRect(m_spriteSheet[0].first, m_spriteSheet[0].second));

    }
    catch (const std::exception& e)
    {
        throw FileException("Deviation from the array");
    }



};

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

void AvatarPower::activatePowerOnPlayer(Player* player) {

    player->getBody()->ApplyLinearImpulseToCenter(b2Vec2(0.f, -1500.f), true);
    player->restartClock();
    player->setPowerOnPlayer(true);
    setPowerIsActive(false);
}

void AvatarPower::draw(sf::RenderWindow& window) const
{
    window.draw(m_sprite);
}


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

    position.x -= 306.f / 2;
    position.y -= 177.f * 0.8;

    m_sprite.setPosition(position);


}

bool AvatarPower::getSideOfPlayer()const {
    return m_PlayerSide;
}
