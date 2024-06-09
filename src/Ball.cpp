#include "Ball.h"
#include "Resources.h"
#include "Keyboard.h"
#include <iostream>

Ball::Ball():m_ballVelocity(5.0f, -10.0f), m_ball(25.0f)
{
	auto texture = &(Resources::getInstance().getBallTexture()[0]); 

	// הגדרת הכדור
    m_sprite.setTexture(*texture);
    m_ball.setTexture(texture);
   // m_ball.set
    m_ball.setOrigin(m_ball.getRadius(), m_ball.getRadius());
    m_ball.setPosition(900.0f, 988.0f); 
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
    m_sprite.setOrigin(m_ball.getOrigin());
    m_sprite.setPosition(m_ball.getPosition());
    //std::cout << m_sprite.getOrigin().x << ' ' << m_sprite.getOrigin().y << ' ' << std::endl;
    //std::cout << m_ball.getOrigin().x << ' ' << m_ball.getOrigin().y << ' ' << std::endl;
    //std::cout << m_sprite.getPosition().x << ' ' << m_sprite.getPosition().y << ' ' << std::endl;
    //std::cout << m_ball.getPosition().x << ' ' << m_ball.getPosition().y << ' ' << std::endl;
    return m_sprite;
}

void Ball::setBallVelocity(sf::Vector2f velocity)
{
    m_ballVelocity = velocity;
}



void  Ball::move(int keyPressed)
{

    float deltaTime = m_clock.restart().asSeconds();

    const float gravity = 980.0f;  // כוח המשיכה בפיקסלים לשנייה בריבוע
    const float restitution = 0.8f;  // מקדם ההתנגשות

    // עדכון המהירות בעקבות כוח המשיכה
    m_ballVelocity.y += gravity * deltaTime;

    // עדכון מיקום הכדור
    m_ball.move(m_ballVelocity * deltaTime);

    //-----------------------------------------------------------------------------------------------
    sf::FloatRect leftTopScoreBar(40.f, 580.f, 150.4f, 631.f);
    sf::FloatRect rightTopScoreBar(1750.f, 580.f, 184.f, 85.f);



    // בדיקת התנגשות עם הקרקע
    if (m_ball.getPosition().y + m_ball.getRadius() >= 835.0f) {
        m_ball.setPosition(m_ball.getPosition().x, 835.0f - m_ball.getRadius());
        m_ballVelocity.y = -m_ballVelocity.y * restitution;
    }



    // בדיקת התנגשות עם הקירות והחלון
    sf::FloatRect ballBounds = m_ball.getGlobalBounds();
    sf::FloatRect windowBounds(0.0f, 0.0f, 1800.0f, 835.0f);

    handleCollision(leftTopScoreBar);
    handleCollision(rightTopScoreBar);


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
    

};



void Ball::handleCollision(const sf::FloatRect& scoreBar) {
    const float restitution = 0.8f;

    float ballLeft = m_ball.getPosition().x - m_ball.getRadius();
    float ballRight = m_ball.getPosition().x + m_ball.getRadius();
    float ballTop = m_ball.getPosition().y - m_ball.getRadius();
    float ballBottom = m_ball.getPosition().y + m_ball.getRadius();

    if (ballRight >= scoreBar.left && ballLeft <= scoreBar.left + scoreBar.width &&
        ballBottom >= scoreBar.top && ballTop <= scoreBar.top + scoreBar.height) {

        if (ballTop < scoreBar.top) {
            // Ball hit the top
            m_ball.setPosition(m_ball.getPosition().x, scoreBar.top - m_ball.getRadius());
            m_ballVelocity.y = -m_ballVelocity.y * restitution;
        }
        else if (ballBottom > scoreBar.top + scoreBar.height) {
            // Ball hit the bottom
            m_ball.setPosition(m_ball.getPosition().x, scoreBar.top + scoreBar.height + m_ball.getRadius());
            m_ballVelocity.y = -m_ballVelocity.y * restitution;
        }
        else if (ballLeft < scoreBar.left) {
            // Ball hit the left side
            m_ball.setPosition(scoreBar.left - m_ball.getRadius(), m_ball.getPosition().y);
            m_ballVelocity.x = -m_ballVelocity.x * restitution;
        }
        else if (ballRight > scoreBar.left + scoreBar.width) {
            // Ball hit the right side
            m_ball.setPosition(scoreBar.left + scoreBar.width + m_ball.getRadius(), m_ball.getPosition().y);
            m_ballVelocity.x = -m_ballVelocity.x * restitution;
        }
    }
}

//void Ball::ballCollisionWithTopGoal() {
//    const float gravity = 980.0f;  // כוח המשיכה בפיקסלים לשנייה בריבוע
//    const float restitution = 0.8f;  // מקדם ההתנגשות
//
//
//    sf::FloatRect leftTopScoreBar(40.f, 580.f, 224.f, 85.f);
//    sf::FloatRect rightTopScoreBar(1750.f, 580.f, 184.f, 85.f); // Width and height are updated to match the original definition
//
//    // Check collision with the left top score bar
//    if (m_ball.getPosition().x + m_ball.getRadius() >= leftTopScoreBar.left &&
//        m_ball.getPosition().x - m_ball.getRadius() <= leftTopScoreBar.left + leftTopScoreBar.width &&
//        m_ball.getPosition().y + m_ball.getRadius() >= leftTopScoreBar.top &&
//        m_ball.getPosition().y - m_ball.getRadius() <= leftTopScoreBar.top + leftTopScoreBar.height) {
//
//        if (m_ball.getPosition().y < leftTopScoreBar.top) {
//            // Ball hit the top
//            m_ball.setPosition(m_ball.getPosition().x, leftTopScoreBar.top - m_ball.getRadius());
//            m_ballVelocity.y = -m_ballVelocity.y * restitution;
//        }
//        else if (m_ball.getPosition().y > leftTopScoreBar.top + leftTopScoreBar.height) {
//            // Ball hit the bottom
//            m_ball.setPosition(m_ball.getPosition().x, leftTopScoreBar.top + leftTopScoreBar.height + m_ball.getRadius());
//            m_ballVelocity.y = -m_ballVelocity.y * restitution;
//        }
//        else if (m_ball.getPosition().x < leftTopScoreBar.left) {
//            // Ball hit the left side
//            m_ball.setPosition(leftTopScoreBar.left - m_ball.getRadius(), m_ball.getPosition().y);
//            m_ballVelocity.x = -m_ballVelocity.x * restitution;
//        }
//        else if (m_ball.getPosition().x > leftTopScoreBar.left + leftTopScoreBar.width) {
//            // Ball hit the right side
//            m_ball.setPosition(leftTopScoreBar.left + leftTopScoreBar.width + m_ball.getRadius(), m_ball.getPosition().y);
//            m_ballVelocity.x = -m_ballVelocity.x * restitution;
//        }
//    }
//
//    // Check collision with the right top score bar
//    if (m_ball.getPosition().x + m_ball.getRadius() >= rightTopScoreBar.left &&
//        m_ball.getPosition().x - m_ball.getRadius() <= rightTopScoreBar.left + rightTopScoreBar.width &&
//        m_ball.getPosition().y + m_ball.getRadius() >= rightTopScoreBar.top &&
//        m_ball.getPosition().y - m_ball.getRadius() <= rightTopScoreBar.top + rightTopScoreBar.height) {
//
//        if (m_ball.getPosition().y < rightTopScoreBar.top) {
//            // Ball hit the top
//            m_ball.setPosition(m_ball.getPosition().x, rightTopScoreBar.top - m_ball.getRadius());
//            m_ballVelocity.y = -m_ballVelocity.y * restitution;
//        }
//        else if (m_ball.getPosition().y > rightTopScoreBar.top + rightTopScoreBar.height) {
//            // Ball hit the bottom
//            m_ball.setPosition(m_ball.getPosition().x, rightTopScoreBar.top + rightTopScoreBar.height + m_ball.getRadius());
//            m_ballVelocity.y = -m_ballVelocity.y * restitution;
//        }
//        else if (m_ball.getPosition().x < rightTopScoreBar.left) {
//            // Ball hit the left side
//            m_ball.setPosition(rightTopScoreBar.left - m_ball.getRadius(), m_ball.getPosition().y);
//            m_ballVelocity.x = -m_ballVelocity.x * restitution;
//        }
//        else if (m_ball.getPosition().x > rightTopScoreBar.left + rightTopScoreBar.width) {
//            // Ball hit the right side
//            m_ball.setPosition(rightTopScoreBar.left + rightTopScoreBar.width + m_ball.getRadius(), m_ball.getPosition().y);
//            m_ballVelocity.x = -m_ballVelocity.x * restitution;
//        }
//    }
//
//
//}

