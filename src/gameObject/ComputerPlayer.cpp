#include "gameObject/ComputerPlayer.h"

ComputerPlayer::ComputerPlayer()
{
}

bool ComputerPlayer::m_registeritComputerPlayer = MovingFactory::registeritMoving("ComputerPlayer",
    []() -> std::shared_ptr<MovingObject> { return std::make_shared<ComputerPlayer>(); });

// פונקציה לעדכון מיקום המחשב
void ComputerPlayer::updateComputerPlayer(sf::RectangleShape& computer, sf::CircleShape& ball,
                                          sf::RectangleShape& computerGoal, float deltaTime) {

    const float speed = 200.0f;  // מהירות המחשב
    const float kickRange = 50.0f;  // טווח הבעיטה
    const float defenseRadius = 300.0f;  // רדיוס שבו המחשב צריך לשמור על השער

    sf::Vector2f direction;
    float length;

    // שמור על השער אם הכדור קרוב לשער המחשב
    if (ball.getPosition().x < defenseRadius) {
        direction = computerGoal.getPosition() - computer.getPosition();
        length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length > 10.0f) {
            direction /= length;
            direction *= speed * deltaTime;
            computer.move(direction);
        }
    }
    else {
        // תקוף את הכדור אם הוא לא קרוב לשער המחשב
        direction = ball.getPosition() - computer.getPosition();
        length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length > kickRange) {
            direction /= length;
            direction *= speed * deltaTime;
            computer.move(direction);
        }
        else {
            //handleKick(ball, computer, m_velocity/computerVelocity);
        }
    }
}

// פונקציה למניעת מעבר הכדור דרך השחקנים
//void handleCollisionWithPlayer(sf::CircleShape& ball, sf::RectangleShape& player, sf::Vector2f& velocity) {
//    if (ball.getGlobalBounds().intersects(player.getGlobalBounds())) {
//        // כיוון ההתנגשות (מרכז הכדור למרכז השחקן)
//        sf::Vector2f direction = ball.getPosition() - player.getPosition();
//        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
//        if (length != 0.0f) {
//            direction /= length; // נרמול הכיוון
//        }
//
//        // העברת הכדור חזרה בעקבות ההתנגשות
//        ball.move(direction * ball.getRadius() * 2.0f);
//
//        // עדכון מהירות הכדור בעקבות ההתנגשות
//        velocity = direction * 300.0f;
//    }
//}
ComputerPlayer::~ComputerPlayer()
{
}