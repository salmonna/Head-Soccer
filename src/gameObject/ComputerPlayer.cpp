#include "gameObject/ComputerPlayer.h"

ComputerPlayer::ComputerPlayer()
{
}

bool ComputerPlayer::m_registeritComputerPlayer = MovingFactory::registeritMoving("ComputerPlayer",
    []() -> std::shared_ptr<MovingObject> { return std::make_shared<ComputerPlayer>(); });

// ������� ������ ����� �����
void ComputerPlayer::updateComputerPlayer(sf::RectangleShape& computer, sf::CircleShape& ball,
                                          sf::RectangleShape& computerGoal, float deltaTime) {

    const float speed = 200.0f;  // ������ �����
    const float kickRange = 50.0f;  // ���� ������
    const float defenseRadius = 300.0f;  // ����� ��� ����� ���� ����� �� ����

    sf::Vector2f direction;
    float length;

    // ���� �� ���� �� ����� ���� ���� �����
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
        // ���� �� ����� �� ��� �� ���� ���� �����
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

// ������� ������ ���� ����� ��� �������
//void handleCollisionWithPlayer(sf::CircleShape& ball, sf::RectangleShape& player, sf::Vector2f& velocity) {
//    if (ball.getGlobalBounds().intersects(player.getGlobalBounds())) {
//        // ����� �������� (���� ����� ����� �����)
//        sf::Vector2f direction = ball.getPosition() - player.getPosition();
//        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
//        if (length != 0.0f) {
//            direction /= length; // ����� ������
//        }
//
//        // ����� ����� ���� ������ ��������
//        ball.move(direction * ball.getRadius() * 2.0f);
//
//        // ����� ������ ����� ������ ��������
//        velocity = direction * 300.0f;
//    }
//}
ComputerPlayer::~ComputerPlayer()
{
}