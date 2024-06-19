#include "power/RegularBehavior.h"
#include "gameObject/Ball.h"


RegularBehavior::RegularBehavior(): m_ballVelocity(5.0f, -10.0f), m_clock()
{
}





void RegularBehavior::performMove(MovingObject * ball)
{

	Ball & ballObject = static_cast<Ball&>(*ball);

    m_ballVelocity = ballObject.getVelocity();

    //sf::Clock& clock = ballObject.getClock();

    if (m_clock.getElapsedTime().asSeconds() >= 1)
    {
        m_clock.restart();
    }

    float deltaTime = m_clock.restart().asSeconds();

    const float gravity = 980.0f;  // כוח המשיכה בפיקסלים לשנייה בריבוע
    const float restitution = 0.8f;  // מקדם ההתנגשות

    // עדכון המהירות בעקבות כוח המשיכה
    m_ballVelocity.y += gravity * deltaTime;

    sf::CircleShape & ballCircle = ballObject.getCircle();

    // עדכון מיקום הכדור
    ballCircle.move(m_ballVelocity * deltaTime);


    // בדיקת התנגשות עם הקרקע
    if (ballCircle.getPosition().y + ballCircle.getRadius() >= 835.0f) {
        ballCircle.setPosition(ballCircle.getPosition().x, 835.0f - ballCircle.getRadius());
        m_ballVelocity.y = -m_ballVelocity.y * restitution;
    }

    // בדיקת התנגשות עם הקירות והחלון
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

    ballObject.setBallVelocity(m_ballVelocity);
}