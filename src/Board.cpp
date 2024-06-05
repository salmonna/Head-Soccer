
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
Board::Board(std::vector<sf::Texture>& texturs):m_boardOpen(true)
{
    m_backGroundStadium.setTexture(texturs[0]);

	//StaticObject* staticObject = std::make_unique<ScoreBoard>(60);
	m_staticObject.push_back(std::make_shared<ScoreBoard>(90));

    m_rightGoal.setRightGoal();
	Keyboard player1(57, 71,72,73,-1,74);
	Keyboard player2(25,0 ,3 ,22 , -1, 18);
	m_movingObject.push_back(std::make_shared<Player>(texturs[1],true, player1));
	m_movingObject.push_back(std::make_shared<Player>(texturs[1], false, player2));

	m_movingObject.push_back(std::make_shared<Ball>());

	m_collidingObject.push_back(m_movingObject[0]);
	m_collidingObject.push_back(m_movingObject[1]);
	m_collidingObject.push_back(m_movingObject[2]);

}

//=============================================== respond =======================================//

// Method to check if a given location corresponds to a stick
void Board::respond(int keyPressed) {


	timeCalculation();
	//m_scoreBoard.updateScore(0, 0);
	m_staticObject[0]->updateScore(0, 0);

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

// Method to draw all sticks in the window
void Board::draw(sf::RenderWindow& window) {

    window.draw(m_backGroundStadium);

    //draw the goals
    m_rightGoal.draw(window);
    m_leftGoal.draw(window);
   

	//draw the score board

	for (int i = 0; i < m_staticObject.size(); i++)
	{
		m_staticObject[i]->draw(window);
	}


	for (int i = 0; i < m_movingObject.size(); i++)
	{
		m_movingObject[i]->draw(window);
	}

}

//check if board is open
bool Board::isOpen() const{

    return m_boardOpen;
}

//=======================================Time==================================
//time calculation
void Board::timeCalculation()
{
	//game board = m_gameObjects[0]
	m_staticObject[0]->timeCalculation();

	if (m_staticObject[0]->timeIsOver())
	{
		m_boardOpen = false;
	}
}