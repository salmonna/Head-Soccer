#include "power/FirePower.h"
#include "gameObject/Ball.h"
#include "Resources.h"


FirePower::FirePower(bool playerSide) :m_ballVelocity(), m_clock(), m_spriteSheetClock(), m_index1(0), m_index2(0),m_playerSide(playerSide)
{
    m_sprite.setTexture(Resources::getInstance().getBallTexture()[2]);

    
    m_spriteSheet.push_back(std::pair(sf::Vector2i(9,81), sf::Vector2i(15,15)));
    m_spriteSheet.push_back(std::pair(sf::Vector2i(38, 75), sf::Vector2i(30, 30)));
    m_spriteSheet.push_back(std::pair(sf::Vector2i(80, 69), sf::Vector2i(45, 45)));
    m_spriteSheet.push_back(std::pair(sf::Vector2i(149, 47), sf::Vector2i(75, 75)));
    m_spriteSheet.push_back(std::pair(sf::Vector2i(265, 36), sf::Vector2i(115, 115)));
    m_spriteSheet.push_back(std::pair(sf::Vector2i(413, 23), sf::Vector2i(130, 130)));
    m_spriteSheet.push_back(std::pair(sf::Vector2i(615, 3), sf::Vector2i(160, 160)));


    m_spriteSheetFlame.push_back(std::pair(sf::Vector2i(0, 194), sf::Vector2i(200, 200)));
    m_spriteSheetFlame.push_back(std::pair(sf::Vector2i(219, 195), sf::Vector2i(200, 200)));
    m_spriteSheetFlame.push_back(std::pair(sf::Vector2i(443, 195), sf::Vector2i(200, 200)));
    m_spriteSheetFlame.push_back(std::pair(sf::Vector2i(653, 194), sf::Vector2i(200, 200)));
};

void FirePower::activatePowerOnBall(b2Body* ballBody)
{

    setPowerIsActive(true);

    // Adjust position if necessary
    b2Vec2 currentPosition = ballBody->GetPosition();
    currentPosition.y -= 8.f; // Move the body 200 pixels higher (adjust as needed)

    ballBody->SetTransform(currentPosition, ballBody->GetAngle());

    // Set awake state to false to "pause" the body
    ballBody->SetAwake(false);
}

void FirePower::activatePowerOnPlayer(b2Body* playerBody) {

    float kickForceX = 500;  // Horizontal kick force
    float kickForceY = -400.2f;  // Vertical kick force (negative for upward)

    b2Vec2 kickForce(kickForceX, kickForceY);
    playerBody->ApplyForceToCenter(kickForce, true);

}

void FirePower::draw(sf::RenderWindow& window, sf::Vector2f position)
{
    if (m_index2 == m_spriteSheetFlame.size())
    {
        m_index2 = 0;
    }

    if (!stayInTheAir() && m_index1 < m_spriteSheet.size())
    {
        if (m_spriteSheetClock.getElapsedTime().asMilliseconds() >= 250.f)
        {
            m_sprite.setTextureRect(sf::IntRect(m_spriteSheet[m_index1].first, m_spriteSheet[m_index1].second));
            m_index1++;
            m_spriteSheetClock.restart();
        }
    }
    else if(m_index2 < m_spriteSheetFlame.size())
    {

        if (m_spriteSheetClock.getElapsedTime().asMilliseconds() >= 250.f)
        {
            m_sprite.setTextureRect(sf::IntRect(m_spriteSheetFlame[m_index2].first, m_spriteSheetFlame[m_index2].second));
            m_index2++;
            m_spriteSheetClock.restart();
        }
    }

    position.x -= 80.f;
    position.y -= 80.f;

    m_sprite.setPosition(position);
    window.draw(m_sprite);

}

bool FirePower::getSideOfPlayer()const {
    return m_playerSide;
}