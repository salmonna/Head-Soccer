
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
Board::Board(Controller* controller, Menu* menu, Pause* pause, GameResults* gameResults) :m_gameState(NULL), m_gameResults(gameResults), m_goalSign(false)
, m_controllerPtr(controller)
{
	std::vector<sf::Texture>& texture = Resources::getInstance().getBoardTexture();
	for (size_t i = 0; i < texture.size()-1; i++)
	{
		m_backGroundStadium.push_back(sf::Sprite());
		m_backGroundStadium[i].setTexture(texture[i]);

	}
	m_backGroundStadium[1].setPosition(0, 674);

	//m_buttons.push_back(std::make_unique<Pause>(menu, this));
	m_buttons.push_back(std::make_unique<Button>(std::move(std::make_unique<SwichScreen>(pause, controller)), Resources::getInstance().getPauseTexture()[0], sf::Vector2f(0.f,0.f))); //pause Button

	m_goalSprite.setTexture(texture[2]);
	m_goalSprite.setPosition(50, 200);


	std::vector<std::string> staticObjectNames { "LeftInsideGoalSide","RightInsideGoalSide", "LeftGoalBack", 
												"RightGoalBack", "LeftGoalTop" , "RightGoalTop" };
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

	ScoreBoard::getInstance().timeCalculation();
	ScoreBoard::getInstance().updateScore(0, 0);

	//------- just for run the computer player--------
	sf::Vector2f ballPosition = m_movingObject[2]->getPosition();
	//------------------------------------------------
	moveAd();

	
	//move the players and the ball
	for (int i = 0; i < m_movingObject.size() - m_goalSign; i++)
	{
		m_movingObject[i]->move(ballPosition);

	}
	
	for_each_pair(m_gameObject.begin() + 2, m_gameObject.end() - 2, [&](auto& a, auto& b) {
		if (collide(*a, *b))
		{
			processCollision(*a, *b);
		}
	});
	
	updateScoreBar();
    if (m_clock.getElapsedTime().asSeconds() > 2)
	{
		m_goalSign = false;
		m_goalSprite.setPosition(0, 200);
	}

	if (m_goalSign)
		m_goalSprite.move(10,0);

	for (int i = 0; i < m_buttons.size(); i++)
	{
		if (m_buttons[i]->contains(pressed)) {

			m_buttons[i]->execute();
			break;
		}
	}

	ScoreBoard::getInstance().Progress();


	if (ScoreBoard::getInstance().timeIsOver())
	{
		m_controllerPtr->setState(m_gameResults);
		reset();
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

//=============================================== update ScoreBar =======================================//
void Board::updateScoreBar() {


	GoalBack& leftGoalBack = dynamic_cast<GoalBack&>(*m_staticObject[2]);
	GoalBack& rightGoalBack = dynamic_cast<GoalBack&>(*m_staticObject[3]);

	if (leftGoalBack.getIfGoal()) {
		m_clock.restart();
		m_goalSign = true;
		m_movingObject[0]->reset();
		m_movingObject[1]->reset();
		ScoreBoard::getInstance().updateScore(0, 1);
		leftGoalBack.setIfGoal(false);
	}
	else if (rightGoalBack.getIfGoal())
	{
		m_clock.restart();
		m_goalSign = true;
		m_movingObject[0]->reset();
		m_movingObject[1]->reset();
		ScoreBoard::getInstance().updateScore(1, 0);
		rightGoalBack.setIfGoal(false);
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

	if (m_goalSign)
		window.draw(m_goalSprite);


	//draw the score board
	ScoreBoard::getInstance().draw(window);

	//draw the game objects
	for (int i = 0; i < m_gameObject.size(); i++)
	{
		m_gameObject[i]->draw(window);
	}
}

