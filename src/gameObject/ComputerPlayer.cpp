#include "gameObject/ComputerPlayer.h"
#include "Resources.h"
#include "power/FirePower.h"

ComputerPlayer::ComputerPlayer():m_numOfJump(0),m_posX(0), m_posY(0), m_move(-2), m_gravity(0)
{

	sf::Vector2f pos(550, 80);

	m_power = std::make_unique<FirePower>(pos);
   
	m_sprite.setTexture(Resources::getInstance().getCharactersTexture()[0]);

	m_basePosition = sf::Vector2f(272, 750);

	m_sprite.setPosition(m_basePosition);

	m_startSprite.push_back(sf::Vector2f(160, 126));
	m_startSprite.push_back(sf::Vector2f(160, 244));
	m_startSprite.push_back(sf::Vector2f(160, 8));
	m_startSprite.push_back(sf::Vector2f(160, 365));

	m_rivalGoal = sf::Vector2f(1680,700);
}

bool ComputerPlayer::m_registeritComputerPlayer = MovingFactory::registeritMoving("ComputerPlayer",
    []() -> std::shared_ptr<MovingObject> { return std::make_shared<ComputerPlayer>(); });

 //ôåð÷öéä ìòãëåï îé÷åí äîçùá
void ComputerPlayer::move(sf::Vector2f ballPosition) {

    const float speed = 200.0f;  // îäéøåú äîçùá
    const float kickRange = 100.0f;  // èååç äáòéèä

    // ëéååï äîçùá ìëéååï äëãåø
    sf::Vector2f direction = ballPosition - m_sprite.getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length > kickRange) {
        //direction /= length; // ðøîåì äëéååï
       //direction *= speed;  // äúàîú îäéøåú äîçùá

        // òãëåï îé÷åí äîçùá
   
		//Right Direction Test
		if (ballPosition.x > m_sprite.getPosition().x ) {

			moveWithRange(4);
			movePlayer(m_startSprite[1], 6, 10);
		}
		//Left Direction Test
		else if (ballPosition.x < m_sprite.getPosition().x) {

			moveWithRange(-4);
			movePlayer(m_startSprite[1], 6, 10);
		}
    }
    else {
		//Upward Direction Test
		if (ballPosition.y < 750) {
			//so jump
			if (m_posY > -180) {
				m_posY -= 25;
			}
			movePlayer(m_startSprite[2], 7, 100);
		}
        //handleKick(ball, player, velocity, userGoal.getPosition());
    }

	updateGravityAndCollision();
}

void ComputerPlayer::reset() {
	m_sprite.setPosition(m_basePosition);
	m_posX = 0;
	m_posY = 0;
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

// Handle gravity and ground collision
void ComputerPlayer::updateGravityAndCollision() {
	if (m_sprite.getPosition().y < 750)
	{
		m_sprite.setPosition(float(m_basePosition.x + m_posX), float(m_basePosition.y + m_posY + m_gravity));
		m_gravity += 5;
	}
	else
	{
		m_gravity = 0;
		m_posY = 0;
	}
}

void ComputerPlayer::moveWithRange(int x) {
	
	if (false)
	{
		if (m_posX + x > -1400 && m_posX + x < 220)
			m_posX += x;
	}
	else
	{
		if (m_posX + x > -220 && m_posX + x < 1400)
			m_posX += x;
	}
}

void ComputerPlayer::draw(sf::RenderWindow& window)const {
	m_power->drawProcess(window);
	window.draw(m_sprite);
}

sf::Vector2f ComputerPlayer::getRivalGoal()const {

	return m_rivalGoal;
}
ComputerPlayer::~ComputerPlayer()
{
}

