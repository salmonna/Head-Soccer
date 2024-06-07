
#pragma once
#include "Board.h"
#include "Resources.h"
#include <fstream>
#include "FileException.h"
#include "Player.h"
#include "StaticObject.h"

#include "Keyboard.h"
#include "Ball.h"
#include "CollisionHandling.h"


// Constructor for the Board class
Board::Board(std::vector<sf::Texture>& texturs):m_boardOpen(true), m_scoreBoard(60)
{
	//update back gound stadium
    m_backGroundStadium.setTexture(texturs[0]);

	//update left and right goals
	auto rGoal = std::make_shared<Goal>();
	rGoal->setRightGoal();
	auto lGoal = std::make_shared<Goal>();
	m_staticObject.push_back(lGoal);
	m_staticObject.push_back(rGoal);
	m_gameObject.push_back(lGoal);
	m_gameObject.push_back(rGoal);


	Keyboard keyPlayer1(57, 71,72,73,-1,74);
	Keyboard keyPlayer2(25,0 ,3 ,22 , -1, 18);
	m_movingObject.push_back(std::make_shared<Player>(texturs[1],true, keyPlayer1));
	m_movingObject.push_back(std::make_shared<Player>(texturs[1], false, keyPlayer2));
	m_gameObject.push_back(m_movingObject[0]);
	m_gameObject.push_back(m_movingObject[1]);
	

	//update ball
	auto ball = std::make_shared<Ball>();
	m_movingObject.push_back(ball);
	m_gameObject.push_back(ball);


	m_collidingObject.push_back(m_movingObject[0]);
	m_collidingObject.push_back(m_movingObject[1]);
	m_collidingObject.push_back(m_movingObject[2]);

}

//=============================================== respond =======================================//

// Method to check if a given location corresponds to a stick
void Board::respond(int keyPressed) {


	timeCalculation();
	m_scoreBoard.updateScore(0, 0);

	//move the players and the ball
	for (int i = 0; i < m_movingObject.size(); i++)
	{
		m_movingObject[i]->move(keyPressed);
	}

	for_each_pair(m_collidingObject.begin(), m_collidingObject.end(), [&](auto& a, auto& b) {
		if (collide(*a, *b))
		{
			processCollision(*a, *b);
		}
	});

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
void Board::draw(sf::RenderWindow& window) {

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