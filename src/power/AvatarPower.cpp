#include "power\AvatarPower.h"
#include "gameObject/Ball.h"
#include "Resources.h"


AvatarPower::AvatarPower() :m_spriteSheetClock(), m_index(0)
{
    m_sprite.setTexture(Resources::getInstance().getPowerTexture()[6]);

    float height = 220.f;

    for (int i = 0; i < 5; i++)
    {
        m_spriteSheet.push_back(std::pair(sf::Vector2i(0, i* height), sf::Vector2i(306.f, height)));
        m_spriteSheet.push_back(std::pair(sf::Vector2i(306.f, i* height), sf::Vector2i(306.f, height)));

    }



};

void AvatarPower::activatePower(sf::CircleShape& ball, sf::Vector2f& currVelocity, sf::Vector2f& direction)
{
    setPowerIsActive(true);

    currVelocity = sf::Vector2f(1500.f, 0.f);
    currVelocity.x *= direction.x;

    m_index = 0;

}


void AvatarPower::draw(sf::RenderWindow& window, sf::Vector2f position)
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
    position.y -= 177.f*0.8;



    m_sprite.setPosition(position);
    window.draw(m_sprite);

}
