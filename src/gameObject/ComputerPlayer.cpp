#include "gameObject/ComputerPlayer.h"
#include "Resources.h"
#include "power/FirePower.h"
#include "gameObject/scoreBoard.h"

ComputerPlayer::ComputerPlayer():m_numOfJump(0), m_jump(false)
{

	sf::Vector2f pos(550, 80);

	m_power = std::make_unique<FirePower>();

   
	m_sprite.setTexture(Resources::getInstance().getCharactersTexture());
	resetToPosition();
	m_basePosition = sf::Vector2f(272, 775);

	//----------------------box2d---------------------------//
	auto world = Box2d::getInstance().getBox2dWorld();
	// Create the player
	b2BodyDef playerBodyDef;
	playerBodyDef.type = b2_dynamicBody;
	playerBodyDef.position.Set(m_basePosition.x / SCALE, m_basePosition.y / SCALE);
	m_body = world->CreateBody(&playerBodyDef);
	b2PolygonShape playerBox;
	playerBox.SetAsBox(30.f / SCALE, 40.f / SCALE);
	b2FixtureDef playerFixtureDef;
	playerFixtureDef.shape = &playerBox;
	playerFixtureDef.density = 10.f;
	playerFixtureDef.friction = 0.4f;
	m_body->CreateFixture(&playerFixtureDef);
	// Set the gravity scale for the player
	m_body->SetGravityScale(PLAYER_GRAVITY_SCALE);

	m_sprite.setOrigin(30.f, 40.f);

	m_startSprite.push_back(sf::Vector2f(160, 126));
	m_startSprite.push_back(sf::Vector2f(160, 244));
	m_startSprite.push_back(sf::Vector2f(160, 8));
	m_startSprite.push_back(sf::Vector2f(160, 365));

	m_rivalGoal = sf::Vector2f(1680,700);
}

bool ComputerPlayer::m_registeritComputerPlayer = MovingFactory::registeritMoving("ComputerPlayer",
    []() -> std::shared_ptr<MovingObject> { return std::make_shared<ComputerPlayer>(); });


void ComputerPlayer::move(sf::Vector2f ballPosition) {

    const float speed = 200.0f;  
    const float kickRange = 100.0f;  
	//const float halfFieldX = 850.0f; // Assuming the field width is 800 units

    sf::Vector2f direction = ballPosition - m_sprite.getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if (m_jump)
	{
		movePlayer(m_startSprite[2], 7, 100);
	}
	update();

    if (length > kickRange) {
		
		if (length > 600 && ballPosition.x > m_sprite.getPosition().x){
			resetToPosition();
			return;
		}

		//Right Direction Test
		if (ballPosition.x > m_sprite.getPosition().x ) {

			m_body->SetLinearVelocity(b2Vec2(7.f, m_body->GetLinearVelocity().y));
			movePlayer(m_startSprite[1], 6, 10);
		}
		//Left Direction Test
		else if (ballPosition.x < m_sprite.getPosition().x) {

			m_body->SetLinearVelocity(b2Vec2(-7.f, m_body->GetLinearVelocity().y));
			movePlayer(m_startSprite[1], 6, 10);
		}
    }
    else if(ballPosition.y < 750 && !m_jump) {
		
		m_jump = true;
		m_body->ApplyLinearImpulseToCenter(b2Vec2(0.f, -JUMP_FORCE), true);
    }

}


void ComputerPlayer::reset() {
	b2Vec2 newPosition(m_basePosition.x / SCALE, m_basePosition.y / SCALE);
	m_body->SetTransform(newPosition, m_body->GetAngle());
	
}

//function that move the player
void ComputerPlayer::movePlayer(sf::Vector2f startPos, int maxSprite, float maxTime) {

	float sec = float(m_moveClock.getElapsedTime().asMilliseconds());
	if (maxTime < sec)
	{
		if (m_numOfJump > 110 * maxSprite)
		{
			m_numOfJump = 0;
			m_jump = false;
			return;
		}
		else
		{
			m_moveClock.restart();
			m_numOfJump += 115;
			resetToPosition(startPos, m_numOfJump);
		}

	}
}

// Reset to default position if not jumping
void ComputerPlayer::resetToPosition(sf::Vector2f startPos, int numOfJump) {

	sf::IntRect characterRect(startPos.x + numOfJump, startPos.y, 80, 90); // Assuming each character is 32x32 pixels
	// Set the texture rectangle to the character's position and size on the sprite sheet
	m_sprite.setTextureRect(characterRect);
	//m_sprite.setPosition(float(m_basePosition.x + m_posX), float(m_basePosition.y + posY));
}

void ComputerPlayer::draw(sf::RenderWindow& window)const {
	ScoreBoard::getInstance().draw(window);
	window.draw(m_sprite);
}

sf::Vector2f ComputerPlayer::getRivalGoal()const {

	return m_rivalGoal;
}

//-----------------------------------------------------------------------------
void ComputerPlayer::update() {
	b2Vec2 position1 = m_body->GetPosition();
	m_sprite.setPosition(B2VecToSFVec(position1));
}

ComputerPlayer::~ComputerPlayer()
{
	std::cout << " C-D" << std::endl;
	m_body->DestroyFixture(m_body->GetFixtureList());
	auto world = Box2d::getInstance().getBox2dWorld();
	world->DestroyBody(m_body);
	m_body = nullptr;
}

