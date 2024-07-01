
#include "power/KameHameHaPower.h"
#include "gameObject/Ball.h"
#include "Resources.h"


KameHameHaPower::KameHameHaPower() :m_spriteSheetClock(), m_index(0)
{
    m_sprite.setTexture(Resources::getInstance().getPowerTexture()[4]);


    m_spriteSheet.push_back(std::pair(sf::Vector2i(35, 38), sf::Vector2i(265.f, 35.f)));
    m_spriteSheet.push_back(std::pair(sf::Vector2i(371, 38), sf::Vector2i(356.f, 55.f)));
    m_spriteSheet.push_back(std::pair(sf::Vector2i(835, 26), sf::Vector2i(390.f, 74.f)));
    m_spriteSheet.push_back(std::pair(sf::Vector2i(0, 133), sf::Vector2i(377.f, 71.f)));
    m_spriteSheet.push_back(std::pair(sf::Vector2i(433, 131), sf::Vector2i(387.f, 76.f)));
    m_spriteSheet.push_back(std::pair(sf::Vector2i(862, 129), sf::Vector2i(376.f, 68.f)));
    m_spriteSheet.push_back(std::pair(sf::Vector2i(0, 250), sf::Vector2i(376.f, 68.f)));
    m_spriteSheet.push_back(std::pair(sf::Vector2i(431, 256), sf::Vector2i(376.f, 68.f)));
    m_spriteSheet.push_back(std::pair(sf::Vector2i(863, 250), sf::Vector2i(394.f, 94.f)));
    m_spriteSheet.push_back(std::pair(sf::Vector2i(3, 360), sf::Vector2i(382.f, 87.f)));
    m_spriteSheet.push_back(std::pair(sf::Vector2i(446, 38), sf::Vector2i(564.f, 68.f)));
    m_spriteSheet.push_back(std::pair(sf::Vector2i(0, 460), sf::Vector2i(567.f, 97.f)));

};

void KameHameHaPower::activatePower(sf::CircleShape& ball, sf::Vector2f& currVelocity, sf::Vector2f& direction)
{
    setPowerIsActive(true);

    currVelocity = sf::Vector2f(1500.f, 0.f);
    currVelocity.x *= direction.x;

    m_index = 0;

}


void KameHameHaPower::draw(sf::RenderWindow& window, sf::Vector2f position)
{
    //if (m_index == m_spriteSheet.size())
    //{
    //    m_index = 0;
    //}

    if (m_spriteSheetClock.getElapsedTime().asMilliseconds() >= 200.f)
    {
        m_sprite.setTextureRect(sf::IntRect(m_spriteSheet[m_index].first, m_spriteSheet[m_index].second));
        if(m_index != m_spriteSheet.size()-1)
            m_index++;

        m_spriteSheetClock.restart();
    }

    position.x -= 40.f;
    position.y -= 40.f;

    m_sprite.setPosition(position);
    window.draw(m_sprite);
}

