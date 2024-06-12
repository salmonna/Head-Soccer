
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


// Constructor for the Board class
Board::Board():m_boardOpen(true), m_scoreBoard(180)
{
	std::vector<sf::Texture>& texturs = Resources::getInstance().getBoardTexture();

	//update back gound stadium
    m_backGroundStadium.setTexture(texturs[0]);

	auto leftInsideSide = std::make_shared<GoalSide>(32, 580, false);
	auto leftBackSide = std::make_shared<GoalBack>(-15, 590, false);
	auto rightInsideSide = std::make_shared<GoalSide>(1755, 580, true);
	auto rightBackSide = std::make_shared<GoalBack>(1805, 590, true);

	auto leftTopBar = std::make_shared<GoalTop>(40, 580, false);
	auto leftOutsideSide = std::make_shared<GoalSide>(-20, 625, false);
	auto rightTopBar = std::make_shared<GoalTop>(1750, 580, true);
	auto rightOutsideSide = std::make_shared<GoalSide>(1810, 625, true);

	m_staticObject.push_back(leftBackSide);
	m_staticObject.push_back(rightBackSide);

	m_gameObject.push_back(leftInsideSide);
	m_gameObject.push_back(rightInsideSide);
	m_gameObject.push_back(leftBackSide);
	m_gameObject.push_back(rightBackSide);
	m_gameObject.push_back(leftTopBar);
	m_gameObject.push_back(rightTopBar);

	Keyboard keyPlayer1(sf::Keyboard::Space, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up,sf::Keyboard::Down);
	Keyboard keyPlayer2(sf::Keyboard::Q, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, sf::Keyboard::S);
	m_movingObject.push_back(std::make_shared<Player>(true, keyPlayer1));
	m_movingObject.push_back(std::make_shared<Player>(false, keyPlayer2));
	//m_client.sendData(*m_movingObject[1]);
	m_gameObject.push_back(m_movingObject[0]);
	m_gameObject.push_back(m_movingObject[1]);

	//update ball
	auto ball = std::make_shared<Ball>();
	m_movingObject.push_back(ball);
	m_gameObject.push_back(ball);

	m_staticObject.push_back(leftBackSide);
	m_staticObject.push_back(rightBackSide);

	m_gameObject.push_back(leftOutsideSide);
	m_gameObject.push_back(rightOutsideSide);

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

	GoalBack& leftGoalBack = dynamic_cast<GoalBack&>(*m_staticObject[0]);
	GoalBack& rightGoalBack = dynamic_cast<GoalBack&>(*m_staticObject[1]);

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