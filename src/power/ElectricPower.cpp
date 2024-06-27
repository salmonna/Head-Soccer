#include "power/ElectricPower.h"
#include "gameObject/Ball.h"
#include "Resources.h"


ElectricPower::ElectricPower() :m_spriteSheetClock(), m_index(0)
{
    m_sprite.setTexture(Resources::getInstance().getPowerTexture()[5]);

    float size = 213.f;

    for (int i = 0; i < 7; i++)
    {
        m_spriteSheet.push_back(std::pair(sf::Vector2i(size *i, 0), sf::Vector2i(size, size)));

    }

    for (int i = 0; i < 7; i++)
    {
        m_spriteSheet.push_back(std::pair(sf::Vector2i(size * i, size), sf::Vector2i(size, size)));

    }

};

void ElectricPower::activatePower(sf::CircleShape& ball, sf::Vector2f& currVelocity, sf::Vector2f& direction)
{
    setPowerIsActive(true);

    currVelocity = sf::Vector2f(1500.f, 0.f);
    currVelocity.x *= direction.x;

    m_index = 0;

}


void ElectricPower::draw(sf::RenderWindow& window, sf::Vector2f position)
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

    position.x -= 213.f / 2;
    position.y -= 213.f / 2;



    m_sprite.setPosition(position);
    window.draw(m_sprite);

}

