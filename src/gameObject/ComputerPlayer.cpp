#include "gameObject/ComputerPlayer.h"
#include "Resources.h"
#include "power/FirePower.h"
#include "gameObject/scoreBoard.h"
#include "gameObject/ScoreBoard.h"
#include "SoundControl.h"

ComputerPlayer::ComputerPlayer(std::shared_ptr<Ball> ball):m_numOfJump(0), m_jump(false),m_aura(false),m_powerOnPlayer(false),m_powerClock(),m_ball(ball)
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
}

bool ComputerPlayer::m_registeritComputerPlayer = MovingFactory::registeritMoving("ComputerPlayer",
    [](std::shared_ptr<Ball> ball) -> std::shared_ptr<MovingObject> { return std::make_shared<ComputerPlayer>(ball); });

//-----------------------------------------------------------------------------
void ComputerPlayer::move() {
 
	sf::Vector2f direction = m_ball->getSprite().getPosition() - m_sprite.getPosition();
	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	if (m_powerOnPlayer && (m_powerClock.getElapsedTime().asSeconds() > 2.f)) {

		deactivatePower(m_body,m_sprite,m_PlayerColor,m_powerOnPlayer);
	}
	else
	{
		updateMovement(m_ball->getSprite().getPosition(), length, direction);
	}
	update();
	checkIfTurnOnAura();
}
//-----------------------------------------------------------------------------
void ComputerPlayer::updateMovement(const sf::Vector2f& ballPosition, float length, const sf::Vector2f& direction) {

	const float kickRange = 100.0f;
	if (m_jump) {
		movePlayer(m_startSprite[2], 7, 100);
	}

	if (length > kickRange) {
		if (length > 500 && ballPosition.x > m_sprite.getPosition().x) {
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
void ComputerPlayer::checkIfTurnOnAura() {

	if (ScoreBoard::getInstance().istProgressP1Full()) {

		ScoreBoard::getInstance().resetProgressP1();
		setAura(true);
	}
}

//-----------------------------------------------------------------------------
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
void ComputerPlayer::update() {
	b2Vec2 position1 = m_body->GetPosition();
	m_sprite.setPosition(B2VecToSFVec(position1));
}
//-----------------------------------------------------------------------------
void ComputerPlayer::draw(sf::RenderWindow& window)const {

	if (m_aura) {
		m_power->drawAura(window, m_sprite.getPosition(), m_sprite.getOrigin());
	}

	window.draw(m_sprite);
}
//-----------------------------------------------------------------------------
b2Body* ComputerPlayer::getBody()const {
	return m_body;
}
//-----------------------------------------------------------------------------
bool ComputerPlayer::getAura()const {

	return m_aura;
}
//-----------------------------------------------------------------------------
bool ComputerPlayer::getSideOfPlayer()const  {

	return false;
}
//-----------------------------------------------------------------------------
void ComputerPlayer::setPowerOnPlayer(bool powerOnPlayer)  {

	m_powerOnPlayer = powerOnPlayer;
}
//-----------------------------------------------------------------------------
bool ComputerPlayer::getPowerOnPlayer() const  {

	return m_powerOnPlayer;
}
//-----------------------------------------------------------------------------
std::shared_ptr<Power> ComputerPlayer::getPower() const  {
	return m_power;
}
//-----------------------------------------------------------------------------
void ComputerPlayer::restartClock() {
	m_powerClock.restart().asSeconds();
}
//-----------------------------------------------------------------------------
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
ComputerPlayer::~ComputerPlayer()
{
	std::cout << " C-D" << std::endl;
	m_body->DestroyFixture(m_body->GetFixtureList());
	auto world = Box2d::getInstance().getBox2dWorld();
	world->DestroyBody(m_body);
	m_body = nullptr;
}