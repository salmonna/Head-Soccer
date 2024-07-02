#include "gameObject/ComputerPlayer.h"
#include "Resources.h"
#include "power/FirePower.h"
#include "gameObject/scoreBoard.h"

ComputerPlayer::ComputerPlayer():m_numOfJump(0), m_jump(false)
{

	sf::Vector2f pos(550, 80);

	std::srand(static_cast<unsigned>(std::time(0)));
	int random_number = std::rand() % 7;
	Resources::getInstance().setSelectedPlayer(random_number);
	m_sprite.setTexture(Resources::getInstance().getCharactersTexture());
	m_power = Resources::getInstance().getPower(false);
	resetToPosition();
	m_basePosition = sf::Vector2f(272, 775);

	//----------------------box2d---------------------------//
	m_body = Box2d::getInstance().createPlayer(m_basePosition);
	m_sprite.setOrigin(30.f, 40.f);

	m_startSprite.push_back(sf::Vector2f(160, 126));
	m_startSprite.push_back(sf::Vector2f(160, 244));
	m_startSprite.push_back(sf::Vector2f(160, 8));
	m_startSprite.push_back(sf::Vector2f(160, 365));

}

bool ComputerPlayer::m_registeritComputerPlayer = MovingFactory::registeritMoving("ComputerPlayer",
    []() -> std::shared_ptr<MovingObject> { return std::make_shared<ComputerPlayer>(); });

//-----------------------------------------------------------------------------
void ComputerPlayer::move(sf::Vector2f ballPosition) {
 
	sf::Vector2f direction = m_ball->getSprite().getPosition() - m_sprite.getPosition();
	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	updateMovement(m_ball->getSprite().getPosition(), length, direction);
}
//-----------------------------------------------------------------------------
void ComputerPlayer::updateMovement(const sf::Vector2f& ballPosition, float length, const sf::Vector2f& direction) {

	const float kickRange = 100.0f;
	if (m_jump) {
		movePlayer(m_startSprite[2], 7, 100);
	}
	update();

	if (length > kickRange) {
		if (length > 600 && ballPosition.x > m_sprite.getPosition().x) {
			resetToPosition();
			return;
		}

		// Right Direction Test
		if (ballPosition.x > m_sprite.getPosition().x) {
			m_body->SetLinearVelocity(b2Vec2(7.f, m_body->GetLinearVelocity().y));
			movePlayer(m_startSprite[1], 6, 10);
		}
		// Left Direction Test
		else if (ballPosition.x < m_sprite.getPosition().x) {
			m_body->SetLinearVelocity(b2Vec2(-7.f, m_body->GetLinearVelocity().y));
			movePlayer(m_startSprite[1], 6, 10);
		}
	}
	else if (ballPosition.y < 750 && !m_jump) {
		m_jump = true;
		m_body->ApplyLinearImpulseToCenter(b2Vec2(0.f, -JUMP_FORCE), true);
	}
}
//-----------------------------------------------------------------------------
void ComputerPlayer::reset() {
	b2Vec2 newPosition(m_basePosition.x / SCALE, m_basePosition.y / SCALE);
	m_body->SetTransform(newPosition, m_body->GetAngle());
	
}
//-----------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------
void ComputerPlayer::update() {
	b2Vec2 position1 = m_body->GetPosition();
	m_sprite.setPosition(B2VecToSFVec(position1));
}
//-----------------------------------------------------------------------------
// Reset to default position if not jumping
void ComputerPlayer::resetToPosition(sf::Vector2f startPos, int numOfJump) {

	sf::IntRect characterRect(startPos.x + numOfJump, startPos.y, 80, 90); // Assuming each character is 32x32 pixels
	// Set the texture rectangle to the character's position and size on the sprite sheet
	m_sprite.setTextureRect(characterRect);
}
//-----------------------------------------------------------------------------
void ComputerPlayer::draw(sf::RenderWindow& window)const {
	ScoreBoard::getInstance().draw(window);
	window.draw(m_sprite);
}
//-----------------------------------------------------------------------------
b2Body* ComputerPlayer::getBody()const {
	return m_body;
}
//-----------------------------------------------------------------------------
void ComputerPlayer::setBall(std::shared_ptr<Ball> ball) {
	m_ball = ball;
}
//-----------------------------------------------------------------------------
ComputerPlayer::~ComputerPlayer()
{
	std::cout << " C-D" << std::endl;
	m_body->DestroyFixture(m_body->GetFixtureList());
	auto world = Box2d::getInstance().getBox2dWorld();
	world->DestroyBody(m_body);
	m_body = nullptr;
}