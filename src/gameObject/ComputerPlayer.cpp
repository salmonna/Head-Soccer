#include "gameObject/ComputerPlayer.h"
#include "Resources.h"

ComputerPlayer::ComputerPlayer():m_numOfJump(0),m_posX(0), m_posY(0), m_move(-2)
{
    std::vector<sf::Texture>& texture = Resources::getInstance().getCharactersTexture();
	m_sprite.setTexture(texture[0]);

	m_basePosition = sf::Vector2f(272, 750);
}


 //פונקציה לעדכון מיקום המחשב
void ComputerPlayer::updateComputerPlayer(/*sf::RectangleShape& player, sf::Vector2f& ballvelocity, */ sf::CircleShape& ball
    /*sf::RectangleShape& userGoal float deltaTime*/) {

    const float speed = 200.0f;  // מהירות המחשב
    const float kickRange = 50.0f;  // טווח הבעיטה

    // כיוון המחשב לכיוון הכדור
    sf::Vector2f direction = ball.getPosition() - m_sprite.getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length > kickRange) {
        direction /= length; // נרמול הכיוון
        direction *= speed;  // התאמת מהירות המחשב

        // עדכון מיקום המחשב
        //player.move(direction * deltaTime);

	

    }
    else {
        //handleKick(ball, player, velocity, userGoal.getPosition());
    }
}



//function that move the player
void ComputerPlayer::movePlayer(sf::Vector2f startPos, int maxSprite, float maxTime) {

	float sec = float(m_moveClock.getElapsedTime().asMilliseconds());
	if (maxTime < sec)
	{
		if (m_numOfJump > 110 * maxSprite)
		{
			m_numOfJump = 0;
			m_move = -2;
			return;
		}
		else
		{
			m_moveClock.restart();
			m_numOfJump += 115;
			resetToPosition(startPos, m_numOfJump, m_posX, m_posY);
		}

	}
}

// Reset to default position if not jumping
void ComputerPlayer::resetToPosition(sf::Vector2f startPos, int numOfJump, int posX, int posY) {

	sf::IntRect characterRect(startPos.x + numOfJump, startPos.y, 80, 90); // Assuming each character is 32x32 pixels
	// Set the texture rectangle to the character's position and size on the sprite sheet
	m_sprite.setTextureRect(characterRect);
	m_sprite.setPosition(float(m_basePosition.x + m_posX), float(m_basePosition.y + posY));
}

//void ComputerPlayer::move(sf::Vector2f pressed) {
//
//    const float speed = 200.0f;  // מהירות המחשב
//    const float kickRange = 50.0f;  // טווח הבעיטה
//
//    // כיוון המחשב לכיוון הכדור
//    sf::Vector2f direction = ball.getPosition() - m_sprite.getPosition();
//    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
//
//    if (length > kickRange) {
//        direction /= length; // נרמול הכיוון
//        direction *= speed;  // התאמת מהירות המחשב
//
//        // עדכון מיקום המחשב
//        //player.move(direction * deltaTime);
//
//
//    }
//    else {
//        //handleKick(ball, player, velocity, userGoal.getPosition());
//    }
//
//}

ComputerPlayer::~ComputerPlayer()
{
}

