#include "power/FirePower.h"
#include "gameObject/Ball.h"
#include "Resources.h"
#include "gameObject/Player.h"
//--------------------------------------------------------------------------------------
// Constructor for the FirePower class
// Initializes the sprite sheet for the fire effect and flame effect
FirePower::FirePower(bool PlayerSide) :m_spriteSheetClock(), m_index1(0), m_index2(0),m_PlayerSide(PlayerSide)
{
    m_sprite.setTexture(Resources::getInstance().getPowerTexture()[8]);
    
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


    try
    {
        m_sprite.setTextureRect(sf::IntRect(m_spriteSheet[0].first, m_spriteSheet[0].second));

    }
    catch (const std::exception&)
    {
        throw FileException("Deviation from the array");
    }

};
//--------------------------------------------------------------------------------------
// Activates the fire power on the ball
// This includes changing the ball's position and awake state
void FirePower::activatePowerOnBall(Ball* ball)
{
    setPowerIsActive(true);

    // Adjust position if necessary
    b2Vec2 currentPosition = ball->getBody()->GetPosition();
    currentPosition.y -= 8.f; // Move the body 200 pixels higher (adjust as needed)
    ball->getBody()->SetTransform(currentPosition, ball->getBody()->GetAngle());

    // Set awake state to false to "pause" the body
    ball->getBody()->SetAwake(false);
}

//--------------------------------------------------------------------------------------
// Activates the fire power on the player
void FirePower::activatePowerOnPlayer(Player* player) {


    player->getSprite().setColor(sf::Color::Black);
    //player->getBody()->SetAwake(false);
    player->restartClock();
    player->setPowerOnPlayer(true);
    setPowerIsActive(false);
}
//--------------------------------------------------------------------------------------
// Draws the fire sprite to the window
void FirePower::draw(sf::RenderWindow& window) const
{
    window.draw(m_sprite);
}

//--------------------------------------------------------------------------------------
// Manages the animation of the fire and flame effects
void FirePower::animation(sf::Vector2f position)
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
    else if (m_index2 < m_spriteSheetFlame.size())
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
}

//--------------------------------------------------------------------------------------
// Returns the side of the player (true if player side, false otherwise)
bool FirePower::getSideOfPlayer()const {
    return m_PlayerSide;
}
