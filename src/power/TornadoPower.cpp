#include "power/TornadoPower.h"
#include "gameObject/Ball.h"
#include "Resources.h"
#include "gameObject/Player.h"

TornadoPower::TornadoPower(bool PlayerSide) :m_spriteSheetClock(), m_index(0), m_PlayerSide(PlayerSide)
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

void TornadoPower::activatePowerOnPlayer(Player* Player) {

    Player->getBody()->ApplyLinearImpulseToCenter(b2Vec2(0.f, -1500.f), true);
    Player->restartClock();
    Player->setPowerOnPlayer(true);
    setPowerIsActive(false);
    player->getBody()->SetAwake(false);
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

bool TornadoPower::getSideOfPlayer()const {
    return m_PlayerSide;
}