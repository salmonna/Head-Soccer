#include "power/TornadoPower.h"
#include "gameObject/Ball.h"
#include "Resources.h"


TornadoPower::TornadoPower() :m_spriteSheetClock(), m_index(0)
{
    m_sprite.setTexture(Resources::getInstance().getPowerTexture()[3]);


    m_spriteSheet.push_back(std::pair(sf::Vector2i(0, 0), sf::Vector2i(334.f, 317.f)));
    m_spriteSheet.push_back(std::pair(sf::Vector2i(327, 0), sf::Vector2i(334.f, 317.f)));
    m_spriteSheet.push_back(std::pair(sf::Vector2i(654, 0), sf::Vector2i(334.f, 317.f)));
    m_spriteSheet.push_back(std::pair(sf::Vector2i(0, 317), sf::Vector2i(334.f, 317.f)));
    m_spriteSheet.push_back(std::pair(sf::Vector2i(327, 317), sf::Vector2i(334.f, 317.f)));
    m_spriteSheet.push_back(std::pair(sf::Vector2i(654, 317), sf::Vector2i(334.f, 317.f)));
    m_spriteSheet.push_back(std::pair(sf::Vector2i(0, 634), sf::Vector2i(334.f, 317.f)));
    m_spriteSheet.push_back(std::pair(sf::Vector2i(327, 634), sf::Vector2i(334.f, 317.f)));
    m_spriteSheet.push_back(std::pair(sf::Vector2i(654, 634), sf::Vector2i(334.f, 317.f)));

};

void TornadoPower::activatePower(sf::CircleShape& ball, sf::Vector2f& currVelocity, sf::Vector2f& direction)
{
    setPowerIsActive(true);

    currVelocity = sf::Vector2f(1500.f, 0.f);
    currVelocity.x *= direction.x;

     m_index = 0;
    
}


void TornadoPower::draw(sf::RenderWindow& window, sf::Vector2f position)
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

    position.x -= 334.f/2;
    position.y -= 317.f*0.9f;



    m_sprite.setPosition(position);
    window.draw(m_sprite);

}

