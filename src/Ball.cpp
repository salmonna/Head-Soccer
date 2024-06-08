#include "Ball.h"
#include "Resources.h"
#include "Keyboard.h"

Ball::Ball():m_ballVelocity(5.0f, -10.0f), m_ball(25.0f)
{

	
	//get ball 1


	auto texture = &(Resources::getInstance().getBallTexture()[0]); 

	// ����� �����
    m_ball.setTexture(texture);
    m_ball.setOrigin(m_ball.getRadius(), m_ball.getRadius());
    m_ball.setPosition(900.0f, 988.0f); 

    m_sprite.setTexture(*texture);
}


void Ball::setPosition(sf::Vector2f position)
{
    m_ball.setPosition(position);
}

sf::Vector2f Ball::getVelocity() const
{
    return m_ballVelocity;

}

sf::Vector2f Ball::getPosition() const
{
    return m_sprite.getPosition();

}

void Ball::draw(sf::RenderWindow & window)
{
	window.draw(m_ball);
}



sf::Sprite & Ball::getSprite()
{
    m_sprite.setPosition(m_ball.getPosition());
    return m_sprite;
}

void Ball::setBallVelocity(sf::Vector2f velocity)
{
    m_ballVelocity = velocity;
}



void  Ball::move(int keyPressed)
{

    float deltaTime = m_clock.restart().asSeconds();

    const float gravity = 980.0f;  // ��� ������ �������� ������ ������
    const float restitution = 0.8f;  // ���� ��������

    // ����� ������� ������ ��� ������
    m_ballVelocity.y += gravity * deltaTime;

    // ����� ����� �����
    m_ball.move(m_ballVelocity * deltaTime);

    // ����� ������� �� �����
    if (m_ball.getPosition().y + m_ball.getRadius() >= 835.0f) {
        m_ball.setPosition(m_ball.getPosition().x, 835.0f - m_ball.getRadius());
        m_ballVelocity.y = -m_ballVelocity.y * restitution;
    }

    // ����� ������� �� ������ ������
    sf::FloatRect ballBounds = m_ball.getGlobalBounds();
    sf::FloatRect windowBounds(0.0f, 0.0f, 1800.0f, 835.0f);

    sf::FloatRect leftTopScoreBar(40.f, 580.f, 224.f, 665.f);
    sf::FloatRect rightTopScoreBar(1750.f, 580.f, 1934.f, 665.f);

    if (ballBounds.left < windowBounds.left) {
        m_ball.setPosition(windowBounds.left + m_ball.getRadius(), m_ball.getPosition().y);
        m_ballVelocity.x = -m_ballVelocity.x * restitution;
    }
    else if (ballBounds.left + ballBounds.width > windowBounds.left + windowBounds.width) {
        m_ball.setPosition(windowBounds.left + windowBounds.width - m_ball.getRadius(), m_ball.getPosition().y);
        m_ballVelocity.x = -m_ballVelocity.x * restitution;
    }
    if (ballBounds.top < windowBounds.top) {
        m_ball.setPosition(m_ball.getPosition().x, windowBounds.top + m_ball.getRadius());
        m_ballVelocity.y = -m_ballVelocity.y * restitution;
    }
    else if (ballBounds.top + ballBounds.height > windowBounds.top + windowBounds.height) {
        m_ball.setPosition(m_ball.getPosition().x, windowBounds.top + windowBounds.height - m_ball.getRadius());
        m_ballVelocity.y = -m_ballVelocity.y * restitution;
    }


    //// ����� ������� �� �-Score Bars
    //if (ballBounds.intersects(leftTopScoreBar) || ballBounds.intersects(rightTopScoreBar)) {
    //    m_ball.setPosition(m_ball.getPosition().x, 1750.0f - m_ball.getRadius());
    //    m_ballVelocity.y = -m_ballVelocity.y * restitution;
    //}

};

