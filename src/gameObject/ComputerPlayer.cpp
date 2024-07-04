#include "gameObject/ComputerPlayer.h"
#include "Resources.h"
#include "power/FirePower.h"
#include "gameObject/scoreBoard.h"
#include "gameObject/ScoreBoard.h"
#include "SoundControl.h"
//-----------------------------------------------------------------------------
// Constructor initializes member variables and sets up the player
ComputerPlayer::ComputerPlayer(std::shared_ptr<Ball>& ball):m_numOfJump(0), m_jump(false),m_aura(false),m_powerOnPlayer(false),m_powerClock(),m_ball(ball), m_body(nullptr)
{

	sf::Vector2f pos(550, 80);

	std::srand(static_cast<unsigned>(std::time(0)));
	int random_number = std::rand() % 7;
	Resources::getInstance().setSelectedPlayer(random_number);
	m_sprite.setTexture(Resources::getInstance().getCharactersTexture());
	m_power = Resources::getInstance().getPower(false);
	resetToPosition(m_sprite,m_basePosition);
	m_basePosition = sf::Vector2f(272, 775);

	//----------------------box2d---------------------------//
	m_body = Box2d::getInstance().createPlayer(m_basePosition);
	m_sprite.setOrigin(30.f, 40.f);

	m_startSprite.push_back(sf::Vector2f(160, 126));
	m_startSprite.push_back(sf::Vector2f(160, 244));
	m_startSprite.push_back(sf::Vector2f(160, 8));
	m_startSprite.push_back(sf::Vector2f(160, 365));

	m_PlayerColor = m_sprite.getColor();

	m_auraSound.setBuffer(Resources::getInstance().getBufferVec()[0]);
	m_auraSound.setVolume(3);
}
//-----------------------------------------------------------------------------
// Static registration of ComputerPlayer in MovingFactory
bool ComputerPlayer::m_registeritComputerPlayer = MovingFactory::registeritMoving("ComputerPlayer",
    [](std::shared_ptr<Ball>& ball) -> std::shared_ptr<MovingObject> { return std::make_shared<ComputerPlayer>(ball); });

//-----------------------------------------------------------------------------
// Move function for updating player behavior
void ComputerPlayer::move() {
 
	sf::Vector2f direction = m_ball->getSprite().getPosition() - m_sprite.getPosition();
	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	if (m_powerOnPlayer && (m_powerClock.getElapsedTime().asSeconds() > 2.f)) 
		deactivatePower(m_body,m_sprite,m_PlayerColor,m_powerOnPlayer);
	else if (!m_powerOnPlayer && m_power->stayInTheAir())
		updateMovement(m_ball->getSprite().getPosition(), length);

	update();
	checkIfTurnOnAura();
}
//-----------------------------------------------------------------------------
// Update player movement based on ball position
void ComputerPlayer::updateMovement(const sf::Vector2f ballPosition, float length) {

	const float kickRange = 100.0f;
	if (m_jump) {
		movePlayer(m_startSprite[2], 7, 100);
	}

	if (length > kickRange) {
		int range = 400 + (std::rand() % (800 - 400 + 1));
		if (length > range && ballPosition.x > m_sprite.getPosition().x) {
			resetToPosition(m_sprite,m_basePosition);
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
// Check if aura should be activated based on game state
void ComputerPlayer::checkIfTurnOnAura() {

	if (ScoreBoard::getInstance().isProgressP1Full()) {

		ScoreBoard::getInstance().resetProgressP1();
		setAura(true);
	}
}

//-----------------------------------------------------------------------------
// Reset player to base position
void ComputerPlayer::reset() {
	b2Vec2 newPosition(m_basePosition.x / SCALE, m_basePosition.y / SCALE);
	m_body->SetTransform(newPosition, m_body->GetAngle());
	
}
//-----------------------------------------------------------------------------
//function that move the Player
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
			resetToPosition(m_sprite,m_basePosition,startPos,m_numOfJump);
		}

	}
}
//-----------------------------------------------------------------------------
// Update player position based on Box2D body
void ComputerPlayer::update() {
	b2Vec2 position1 = m_body->GetPosition();
	m_sprite.setPosition(B2VecToSFVec(position1));
}
//-----------------------------------------------------------------------------
// Draw function to render player and aura effect
void ComputerPlayer::draw(sf::RenderWindow& window)const {

	if (m_aura) {
		m_power->drawAura(window, m_sprite.getPosition(), m_sprite.getOrigin());
	}

	window.draw(m_sprite);
}
//-----------------------------------------------------------------------------
// Getter function to retrieve Box2D body of the player
b2Body* ComputerPlayer::getBody()const {
	return m_body;
}
//-----------------------------------------------------------------------------
// Getter function to check if aura effect is active
bool ComputerPlayer::getAura()const {

	return m_aura;
}
//-----------------------------------------------------------------------------
// Function to indicate player side (always false for computer player)
bool ComputerPlayer::getSideOfPlayer()const  {

	return false;
}
//-----------------------------------------------------------------------------
// Setter function to set power effect on player
void ComputerPlayer::setPowerOnPlayer(bool powerOnPlayer)  {

	m_powerOnPlayer = powerOnPlayer;
}
//-----------------------------------------------------------------------------
// Getter function to check if power effect is active on player
bool ComputerPlayer::getPowerOnPlayer() const  {

	return m_powerOnPlayer;
}
//-----------------------------------------------------------------------------
// Getter function to retrieve current power of the player
std::shared_ptr<Power> ComputerPlayer::getPower() const  {
	return m_power;
}
//-----------------------------------------------------------------------------
// Restart power clock for the player
void ComputerPlayer::restartClock() {
	m_powerClock.restart().asSeconds();
}
//-----------------------------------------------------------------------------
// Setter function to activate or deactivate aura effect
void ComputerPlayer::setAura(bool aura) {

	if (!m_aura && aura) {
		m_auraSound.play();
		m_auraSound.setLoop(true);
	}
	else
		m_auraSound.stop();

	m_aura = aura;
}
//-----------------------------------------------------------------------------
// Destructor to clean up Box2D body and fixtures
ComputerPlayer::~ComputerPlayer()
{
	m_body->DestroyFixture(m_body->GetFixtureList());
	auto world = Box2d::getInstance().getBox2dWorld();
	world->DestroyBody(m_body);
	m_body = nullptr;
}