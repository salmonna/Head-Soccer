#include "power/FirePower.h"
#include "gameObject/Ball.h"
#include "Resources.h"


FirePower::FirePower() :m_ballVelocity(), m_clock()
{



};


void FirePower::performMove(Ball* ball)
{

    m_ballVelocity = ball->getVelocity();

    if (m_clock.getElapsedTime().asSeconds() >= 1)
    {
        m_clock.restart();
       
    }

    if (isTimeIsOver())
    {
        ball->setMoveBehavior(std::make_shared<RegularBehavior>());
        ball->getCircle().setTexture(&Resources::getInstance().getBallTexture()[0]);
    }

    float deltaTime = m_clock.restart().asSeconds();
    const float gravity = 980.0f;  // ��� ������ �������� ������ ������
    const float restitution = 0.8f;  // ���� ��������

    // ����� ������� ������ ��� ������
    m_ballVelocity.y += gravity * deltaTime;

    sf::CircleShape& ballCircle = ball->getCircle();

    // ����� ����� �����
    ballCircle.move(m_ballVelocity * deltaTime);


    // ����� ������� �� �����
    if (ballCircle.getPosition().y + ballCircle.getRadius() >= 835.0f) {
        ballCircle.setPosition(ballCircle.getPosition().x, 835.0f - ballCircle.getRadius());
        m_ballVelocity.y = -m_ballVelocity.y * restitution;
    }

    // ����� ������� �� ������ ������
    sf::FloatRect ballBounds = ballCircle.getGlobalBounds();
    sf::FloatRect windowBounds(0.0f, 0.0f, 1800.0f, 835.0f);


    if (ballBounds.left < windowBounds.left) {
        ballCircle.setPosition(windowBounds.left + ballCircle.getRadius(), ballCircle.getPosition().y);
        m_ballVelocity.x = -m_ballVelocity.x * restitution;
    }
    else if (ballBounds.left + ballBounds.width > windowBounds.left + windowBounds.width) {
        ballCircle.setPosition(windowBounds.left + windowBounds.width - ballCircle.getRadius(), ballCircle.getPosition().y);
        m_ballVelocity.x = -m_ballVelocity.x * restitution;
    }
    if (ballBounds.top < windowBounds.top) {
        ballCircle.setPosition(ballCircle.getPosition().x, windowBounds.top + ballCircle.getRadius());
        m_ballVelocity.y = -m_ballVelocity.y * restitution;
    }
    else if (ballBounds.top + ballBounds.height > windowBounds.top + windowBounds.height) {
        ballCircle.setPosition(ballCircle.getPosition().x, windowBounds.top + windowBounds.height - ballCircle.getRadius());
        m_ballVelocity.y = -m_ballVelocity.y * restitution;
    }

    ball->setBallVelocity(m_ballVelocity);

}


void FirePower::activatePower(sf::CircleShape& ball, sf::Vector2f& currVelocity, sf::Vector2f & direction)
{
    currVelocity = sf::Vector2f(1500.f, 0.f);
    currVelocity.x *= direction.x;
    sf::Vector2f currPos = ball.getPosition();
    currPos.y -= 300.f;
    ball.setPosition(currPos);
    //ball.setFillColor(sf::Color(255, 255, 255, 64));
    ball.setTexture(&Resources::getInstance().getBallTexture()[2]);
}



void FirePower::draw(sf::RenderWindow& window) const
{


}