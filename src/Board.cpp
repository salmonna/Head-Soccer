
#pragma once
#include "Board.h"
#include "Resources.h"
#include <fstream>
#include "FileException.h"
#include "Player.h"

#include "StaticObject.h"


// Constructor for the Board class
Board::Board(std::vector<sf::Texture>& texturs):m_boardOpen(true),m_jump(0),m_pos(0)
{
    m_backGroundStadium.setTexture(texturs[0]);


	//StaticObject* staticObject = std::make_unique<ScoreBoard>(60);
	m_gameObjects.push_back(std::make_unique<ScoreBoard>(60));


    m_rightGoal.setRightGoal();

	m_movingObject.push_back(std::make_unique<Player>(texturs[2]));


}

//=============================================== respond =======================================//

// Method to check if a given location corresponds to a stick
void Board::respond(int keyPressed) {


	timeCalculation();
	//m_scoreBoard.updateScore(0, 0);
	m_gameObjects[0]->updateScore(0, 0);

	for (int i = 0; i < m_movingObject.size(); i++)
	{
		m_movingObject[i]->move(keyPressed);
	}

}

//=============================================== draw =======================================//

// Method to draw all sticks in the window
void Board::draw(sf::RenderWindow& window) {

    window.draw(m_backGroundStadium);

    //draw the goals
    m_rightGoal.draw(window);
    m_leftGoal.draw(window);
   

	//draw the score board

	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw(window);
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
	m_gameObjects[0]->timeCalculation();

	if (m_gameObjects[0]->timeIsOver())
	{
		m_boardOpen = false;
	}
}