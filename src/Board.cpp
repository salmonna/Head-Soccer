
#pragma once
#include "Board.h"
#include "Resources.h"
#include <fstream>
#include "FileException.h"
#include "Player.h"
#include "StaticObject.h"
#include "Ball.h"

// Constructor for the Board class
Board::Board(std::vector<sf::Texture>& texturs):m_boardOpen(true)
{
    m_backGroundStadium.setTexture(texturs[0]);
	auto scoreBoard = std::make_shared<ScoreBoard>(60);
	m_staticObject.push_back(scoreBoard);
	m_gameObject.push_back(scoreBoard);


	auto rGoal = std::make_shared<Goal>();
	rGoal->setRightGoal();
	auto lGoal = std::make_shared<Goal>();
	m_staticObject.push_back(lGoal);
	m_staticObject.push_back(rGoal);
	m_gameObject.push_back(lGoal);
	m_gameObject.push_back(rGoal);




    //m_rightGoal.setRightGoal();

	auto player1 = std::make_shared<Player>(texturs[1]);
	m_movingObject.push_back(player1);
	m_gameObject.push_back(player1);


	auto ball = std::make_shared<Ball>();
	m_movingObject.push_back(ball);
	m_gameObject.push_back(ball);


}

//=============================================== respond =======================================//

// Method to check if a given location corresponds to a stick
void Board::respond(int keyPressed) {


	//timeCalculation();
	//m_scoreBoard.updateScore(0, 0);
	//m_staticObject[0]->updateScore(0, 0);

	for (int i = 0; i < m_movingObject.size(); i++)
	{
		m_movingObject[i]->move(keyPressed);
	}

}

//=============================================== draw =======================================//

// Method to draw all objects in the window
void Board::draw(sf::RenderWindow& window) {

    window.draw(m_backGroundStadium);

    //draw the goals
    //m_rightGoal.draw(window);
    //m_leftGoal.draw(window);
   

	//draw the score board

	for (int i = 0; i < m_gameObject.size(); i++)
	{
		m_gameObject[i]->draw(window);
	}


	//for (int i = 0; i < m_movingObject.size(); i++)
	//{
	//	m_movingObject[i]->draw(window);
	//}

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
	//m_staticObject[0]->timeCalculation();

	//if (m_staticObject[0]->timeIsOver())
	//{
	//	m_boardOpen = false;
	//}
}