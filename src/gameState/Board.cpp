
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
	m_backGroundStadium[1].setPosition(0, 670);

	//m_buttons.push_back(std::make_unique<Pause>(menu, this));
	m_buttons.push_back(std::make_unique<Button>(std::move(std::make_unique<SwichScreen>(pause, controller)), Resources::getInstance().getPauseTexture()[0]
													, sf::Vector2f(0.f,0.f))); //pause Button


	std::vector<std::string> staticObjectNames { "LeftInsideGoalSide","RightInsideGoalSide", "LeftGoalBack", 
												"RightGoalBack", "LeftGoalTop" , "RightGoalTop" };
	createStaticObjects(staticObjectNames);


	m_box2dWorld = Box2d::getInstance().getBox2dWorld();

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

	

	//------- just for run the computer player--------
	sf::Vector2f ballPosition = m_movingObject[2]->getPosition();
	//------------------------------------------------
	
	handleScoreBoard();
	moveAd();
	

	//move the players and the ball
	for (int i = 0; i < m_movingObject.size() && !ScoreBoard::getInstance().isGoal(); i++)
	{
		m_movingObject[i]->move(ballPosition);

	}
	
	for_each_pair(m_gameObject.begin() + 2, m_gameObject.end() - 2, [&](auto& a, auto& b) {
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
	ScoreBoard::getInstance().updateScore(0, 0);
	ScoreBoard::getInstance().Progress();
	if (ScoreBoard::getInstance().timeIsOver())
	{
		m_controllerPtr->setState(m_gameResults);
		reset();
	}

	if (!ScoreBoard::getInstance().isGoal())
	{
		float timeStep = 1.f / 60.f;
		int32 velocityIterations = 6;
		int32 positionIterations = 3;
		m_box2dWorld->Step(timeStep, velocityIterations, positionIterations);
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
		sprite.setPosition(-sprite.getGlobalBounds().width, 680);
	}

}

void Board::reset() {
	int size = m_gameObject.size() - 6;
	for (int i = 0; i < size; i++)
	{
		m_gameObject.pop_back();
	}
	m_movingObject.clear();
	size = m_staticObject.size() - 6;
	for (int i = 0; i < size; i++)
	{
		m_staticObject.pop_back();
	}
	ScoreBoard::getInstance().reset();
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

	//if (m_goalSign)
	//	window.draw(m_goalSprite);


	//draw the score board
	ScoreBoard::getInstance().draw(window);

	//draw the game objects
	for (int i = 0; i < m_gameObject.size(); i++)
	{
		m_gameObject[i]->draw(window);
	}
}

