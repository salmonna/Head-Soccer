#include "ComputerPlayer.h"

ComputerPlayer::ComputerPlayer()
{
}

// ������� ������ ����� �����
void ComputerPlayer::updateComputerPlayer(/*sf::RectangleShape& player, sf::Vector2f& ballvelocity, */ sf::CircleShape & ball,
                                          sf::RectangleShape& userGoal,/* float deltaTime*/) {

    const float speed = 200.0f;  // ������ �����
    const float kickRange = 50.0f;  // ���� ������

    // ����� ����� ������ �����
    sf::Vector2f direction = ball.getPosition() - m_comPlayerSprite.getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length > kickRange) {
        direction /= length; // ����� ������
        direction *= speed;  // ����� ������ �����

        // ����� ����� �����
        //player.move(direction * deltaTime);
    }
    else {
        //handleKick(ball, player, velocity, userGoal.getPosition());
    }
}

ComputerPlayer::~ComputerPlayer()
{
}

