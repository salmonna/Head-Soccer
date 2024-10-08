#pragma once
#include "gameState/Board.h"
#include "Resources.h"
#include "FileException.h"
#include "gameObject/StaticObject.h"
#include "Keyboard.h"
#include "gameObject/Ball.h"
#include "CollisionHandling.h"
#include "Factory/MovingFactory.h"
#include "Factory/StaticFactory.h"
#include "gameState/GameResults.h"
#include "Command/SwichScreen.h"
#include "Command/Command.h"


//-------------------------------- Constructor -----------------------------------
// Constructor initializes the Board class with necessary components
Board::Board(Controller* controller, Pause* pause, GameResults* gameResults) :m_gameResults(gameResults),m_controllerPtr(controller)
{
	
	std::vector<sf::Texture>& texture = Resources::getInstance().getBoardTexture();
	for (size_t i = 0; i < texture.size(); i++)
	{
		m_backGroundStadium.push_back(sf::Sprite());
		m_backGroundStadium[i].setTexture(texture[i]);
	}
	m_backGroundStadium[1].setPosition(0, 674);
	auto ball = std::make_shared<Ball>();
	m_buttons.push_back(std::make_unique<Button>(std::move(std::make_unique<SwichScreen>(pause, controller)),
						Resources::getInstance().getPauseTexture()[0], sf::Vector2f(1670.f, 45.f))); //pause Button

	std::vector<std::string> staticObjectNames { "LeftOutsideGoalSide" , "RightOutsideGoalSide", "LeftInsideGoalSide","RightInsideGoalSide", "LeftGoalTop" , "RightGoalTop",
												"LeftGoalBack", "RightGoalBack" };
	createStaticObjects(staticObjectNames);
	auto object = MovingFactory::createMoving("Ball", ball);

	if (object)
	{
		m_movingObject.push_back(object);
		m_gameObject.push_back(object);
	}
	else
		std::cout << "Class not found!\n";

}
//--------------------------------------------------------------------------------
// Method to create moving objects based on names provided
void Board::createMovingObjects(const std::vector<std::string>& objectNames)
{
	std::shared_ptr<Ball> ballObject = std::dynamic_pointer_cast<Ball>(m_movingObject[0]);
	for (const auto& name : objectNames) {
		auto object = MovingFactory::createMoving(name, ballObject);

		if (object)
		{
			m_movingObject.push_back(object);
			m_gameObject.push_back(object);
		}
		else
			std::cout << "Class not found!\n";
	}
	ScoreBoard::getInstance().setFlagsPlayers();

}
//--------------------------------------------------------------------------------
// Method to create static objects based on names provided
void Board::createStaticObjects(const std::vector<std::string>& objectNames)
{
	for (const auto& name : objectNames) {
		auto object = StaticFactory::createStatic(name);

		if (object)
		{
			m_staticObject.push_back(object);
			m_gameObject.push_back(object);
		}
		else
			std::cout << "Class not found!\n";
	}
}

//=============================================== respond =======================================//

// Method to check if a given location corresponds to a stick
void Board::respond(sf::Vector2f pressed) {
	
	handleScoreBoard();
	moveAd();

	//move the Players and the ball
	for (int i = 0; i < m_movingObject.size() && !ScoreBoard::getInstance().isGoal(); i++)
	{
		m_movingObject[i]->move();
	}
	
	for_each_pair(m_gameObject.begin() + 6, m_gameObject.end(), [&](auto& a, auto& b) {
		if (collide(*a, *b))
		{
			processCollision(*a, *b);
		}
	});

	for (int i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i]->respond();

		if (m_buttons[i]->contains(pressed)) {

			m_buttons[i]->execute();
			break;
		}
	}
}

//--------------------------------------------------------------------------------
// Method to update score board and manage game state
void Board::handleScoreBoard() {

	ScoreBoard::getInstance().updateScore(0, 0);
	ScoreBoard::getInstance().timeCalculation();
	ScoreBoard::getInstance().Progress();
	if (ScoreBoard::getInstance().timeIsOver())
	{
		m_controllerPtr->setState(m_gameResults);
		reset();
	}
	else if (ScoreBoard::getInstance().isGoal())
	{
		for (auto& object : m_movingObject)
			object->reset();
	}
	else
	{
		Box2d::getInstance().step();
	}
}

//--------------------------------------------------------------------------------
// Method to move advertisement on stadium background
void Board::moveAd()
{

	sf::Sprite& sprite = m_backGroundStadium[1];
	sprite.move(1.5, 0);

	if (sprite.getPosition().x >= 1800)
	{
		sprite.setPosition(-sprite.getGlobalBounds().width, 674);
	}

}
//--------------------------------------------------------------------------------
// Method to reset game state
void Board::reset() {
	for (auto& object : m_movingObject)
		object->reset();

	m_gameObject.erase(m_gameObject.begin() + 9, m_gameObject.end());
	m_movingObject.erase(m_movingObject.begin() + 1, m_movingObject.end());
}

//=============================================== for_each_pair =======================================//

// STL-like algorithm to run over all pairs
template <typename FwdIt, typename Fn>
void Board::for_each_pair(FwdIt begin, FwdIt end, Fn fn)
{
	for (; begin != end; ++begin)
		for (auto second = begin + 1; second != end; ++second)
			fn(*begin, *second);
}
//=============================================== collide =======================================//
bool Board::collide(GameObject& a, GameObject& b) {
	// Get the AABBs for the first fixture of each body
	const b2AABB& aabbA = a.getBody()->GetFixtureList()->GetAABB(0);
	const b2AABB& aabbB = b.getBody()->GetFixtureList()->GetAABB(0);

	// Check for intersection between AABBs
	return (aabbA.lowerBound.x <= aabbB.upperBound.x && aabbA.upperBound.x >= aabbB.lowerBound.x &&
		aabbA.lowerBound.y <= aabbB.upperBound.y && aabbA.upperBound.y >= aabbB.lowerBound.y);
}
//=============================================== draw =======================================//
// Method to draw all objects in the window
void Board::draw(sf::RenderWindow& window) const{

	//draw game objects
	drawGameObjects(window);

	for (int i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i]->draw(window);
	}
}
//--------------------------------------------------------------------------------
//draw game objects
void  Board::drawGameObjects(sf::RenderWindow& window) const
{
	//draw the back ground stadium and field
	for (int i = 0; i < m_backGroundStadium.size(); i++)
	{
		window.draw(m_backGroundStadium[i]);
	}

	//draw the score board
	ScoreBoard::getInstance().draw(window);

	//draw the game objects
	for (int i = 2; i < m_gameObject.size(); i++)
	{
		m_gameObject[i]->draw(window);
	}
	m_gameObject[0]->draw(window);
	m_gameObject[1]->draw(window);
}