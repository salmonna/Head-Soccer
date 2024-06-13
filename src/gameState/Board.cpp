
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

// Constructor for the Board class
Board::Board() :m_boardOpen(true), m_scoreBoard(10)
{
	std::vector<sf::Texture>& texturs = Resources::getInstance().getBoardTexture();

	//update back gound stadium
	m_backGroundStadium.setTexture(texturs[0]);

	std::vector<std::string> staticObjectNames { "LeftInsideGoalSide","RightInsideGoalSide", "LeftGoalBack", 
													"RightGoalBack", "LeftGoalTop" , "RightGoalTop" };


	std::vector<std::string> movingObjectNames{ "RightPlayer", "LeftPlayer", "Ball" };

	createStaticObjects(staticObjectNames);
	createMovingObjects(movingObjectNames);

	staticObjectNames = { "LeftOutsideGoalSide" , "RightOutsideGoalSide" };

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


	timeCalculation();
	m_scoreBoard.updateScore(0, 0);

	//move the players and the ball
	for (int i = 0; i < m_movingObject.size(); i++)
	{
		m_movingObject[i]->move(pressed);

	}

	for_each_pair(m_gameObject.begin() + 2, m_gameObject.end() - 2, [&](auto& a, auto& b) {
		if (collide(*a, *b))
		{
			processCollision(*a, *b);
		}
	});

	updateScoreBar();

}

//=============================================== update ScoreBar =======================================//
void Board::updateScoreBar() {


	GoalBack& leftGoalBack = dynamic_cast<GoalBack&>(*m_staticObject[2]);
	GoalBack& rightGoalBack = dynamic_cast<GoalBack&>(*m_staticObject[3]);

	if (leftGoalBack.getIfGoal()) {

		m_scoreBoard.updateScore(0, 1);
		leftGoalBack.setIfGoal(false);
	}
	else if (rightGoalBack.getIfGoal())
	{
		m_scoreBoard.updateScore(1, 0);
		rightGoalBack.setIfGoal(false);
	}

}

GameState* Board::handleEvents()
{
	if (m_scoreBoard.timeIsOver())
	{
		auto resultsMode = GameResults();
		return &resultsMode;
	}
	return NULL;
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
bool Board::collide(GameObject& a, GameObject& b)
{
	return a.getSprite().getGlobalBounds().intersects(b.getSprite().getGlobalBounds());
}
//=============================================== draw =======================================//

// Method to draw all objects in the window
void Board::draw(sf::RenderWindow& window) const{

	//draw the back ground stadium and field
    window.draw(m_backGroundStadium);

	//draw the game objects
	for (int i = 0; i < m_gameObject.size(); i++)
	{
		m_gameObject[i]->draw(window);
	}

	//draw the score board
	m_scoreBoard.draw(window);

}

//check if board is open
bool Board::isOpen() const{

    return m_boardOpen;
}

//=======================================Time==================================
//time calculation
void Board::timeCalculation()
{
	//game board = m_gameObjects[0];
	m_scoreBoard.timeCalculation();

	if (m_scoreBoard.timeIsOver())
	{
		m_boardOpen = false;
	}
}