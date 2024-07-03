
#pragma once
#include "gameState/Board.h"
#include "Resources.h"
#include <fstream>
#include "FileException.h"
#include "gameObject/Player.h"
#include "gameObject/StaticObject.h"
#include "Keyboard.h"
#include "gameObject/Ball.h"
#include "CollisionHandling.h"
#include "gameObject/GoalSide.h"
#include "gameObject/GoalBack.h"
#include "gameObject/GoalTop.h"
#include "Factory/MovingFactory.h"
#include "Factory/StaticFactory.h"
#include "gameState/GameResults.h"
#include "Command/SwichScreen.h"
#include "Command/Command.h"


// Constructor for the Board class
Board::Board(Controller* controller, Menu* menu, Pause* pause, GameResults* gameResults) :m_gameState(NULL), m_gameResults(gameResults),m_controllerPtr(controller)
{
	
	std::vector<sf::Texture>& texture = Resources::getInstance().getBoardTexture();
	for (size_t i = 0; i < texture.size(); i++)
	{
		m_backGroundStadium.push_back(sf::Sprite());
		m_backGroundStadium[i].setTexture(texture[i]);

	}
	m_backGroundStadium[1].setPosition(0, 674);

	m_buttons.push_back(std::make_unique<Button>(std::move(std::make_unique<SwichScreen>(pause, controller)),
						Resources::getInstance().getPauseTexture()[0], sf::Vector2f(0.f,0.f))); //pause Button

	std::vector<std::string> staticObjectNames { "LeftOutsideGoalSide" , "RightOutsideGoalSide", "LeftInsideGoalSide","RightInsideGoalSide", "LeftGoalTop" , "RightGoalTop",
												"LeftGoalBack", "RightGoalBack" };
	createStaticObjects(staticObjectNames);
}

void Board::createMovingObjects(const std::vector<std::string>& objectNames)
{

	for (const auto& name : objectNames) {
		auto object = MovingFactory::createMoving(name);

		if (object)
		{
			m_movingObject.push_back(object);
			m_gameObject.push_back(object);
		}
		else
			std::cout << "Class not found!\n";
	}
	if (objectNames[1] == "ComputerPlayer")
	{
		// Assuming m_movingObject is a vector or array of std::shared_ptr<BaseClass>
		std::shared_ptr<Ball> ballObject = std::dynamic_pointer_cast<Ball>(m_movingObject[2]);
		std::shared_ptr<ComputerPlayer> computerObject = std::dynamic_pointer_cast<ComputerPlayer>(m_movingObject[1]);

		computerObject->setBall(ballObject);
	}
	ScoreBoard::getInstance().setFlagsPlayers();

}

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

	//move the players and the ball
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
		if (m_buttons[i]->contains(pressed)) {

			m_buttons[i]->execute();
			break;
		}
	}
}

//----------------handle Score Board---------------//
void Board::handleScoreBoard() {

	ScoreBoard::getInstance().timeCalculation();
	ScoreBoard::getInstance().Progress();
	if (ScoreBoard::getInstance().timeIsOver())
	{
		m_controllerPtr->setState(m_gameResults);
		reset();
	}
	else if (!ScoreBoard::getInstance().isGoal())
	{
		Box2d::getInstance().step();
	}
	else
	{
		m_movingObject[0]->reset();
		m_movingObject[1]->reset();
	}
}


void Board::moveAd()
{

	sf::Sprite& sprite = m_backGroundStadium[1];
	sprite.move(1.5, 0);

	if (sprite.getPosition().x >= 1800)
	{
		sprite.setPosition(-sprite.getGlobalBounds().width, 674);
	}

}

void Board::reset() {
	m_gameObject.erase(m_gameObject.begin() + 8, m_gameObject.end());
	m_movingObject.clear();
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