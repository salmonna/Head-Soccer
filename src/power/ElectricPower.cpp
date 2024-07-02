#include "power/ElectricPower.h"
#include "gameObject/Player.h"
#include "gameObject/Ball.h"
#include "Resources.h"


ElectricPower::ElectricPower(bool playerSide) :m_spriteSheetClock(), m_index(0), m_playerSide(playerSide)
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

    try
    {
        m_sprite.setTextureRect(sf::IntRect(m_spriteSheet[0].first, m_spriteSheet[0].second));

    }
    catch (const std::exception& e)
    {
        throw FileException("Deviation from the array");
    }

};

void ElectricPower::activatePowerOnBall(Ball* ball)
{
    setPowerIsActive(true);

    // Adjust position if necessary
    b2Vec2 currentPosition = ball->getBody()->GetPosition();
    currentPosition.y -= 5.f; // Move the body 200 pixels higher (adjust as needed)
    ball->getBody()->SetTransform(currentPosition, ball->getBody()->GetAngle());

    // Set awake state to false to "pause" the body
    ball->getBody()->SetAwake(false);
}

void ElectricPower::activatePowerOnPlayer(Player* player) {

    //need to fix this power
    Box2d::getInstance().step();


    // Adjust position if necessary
    b2Vec2 currentPosition = player->getBody()->GetPosition();
    currentPosition.y = 60.f; //make the player disapear
    player->getBody()->SetTransform(currentPosition, player->getBody()->GetAngle());

    player->restartClock();
    player->setPowerOnPlayer(true); //freexe plower
    setPowerIsActive(false);
}

void ElectricPower::draw(sf::RenderWindow& window) const
{
    window.draw(m_sprite);
}

void ElectricPower::animation(sf::Vector2f position)
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
}


bool ElectricPower::getSideOfPlayer()const {
    return m_playerSide;
}