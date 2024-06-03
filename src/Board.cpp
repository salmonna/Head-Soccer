
#pragma once
#include "Board.h"
#include "Resources.h"
#include <fstream>
#include "FileException.h"


// Constructor for the Board class
Board::Board(std::vector<sf::Texture>& texturs):m_boardOpen(true), m_scoreBoard(120)
{

	for (int i = 0; i < texturs.size(); i++)
	{
		auto sprite = sf::Sprite(texturs[i]);
		m_vecSprits.push_back(sprite);
	}
	m_vecSprits[1].setPosition(-40,630);
	m_vecSprits[1].scale(0.6,0.6);
}

//=============================================== respond =======================================//

// Method to check if a given location corresponds to a stick
void Board::respond(sf::Vector2f loc) {

    
}

//=============================================== draw =======================================//

// Method to draw all sticks in the window
void Board::draw(sf::RenderWindow& window) {
   
	for (int i = 0; i < m_vecSprits.size(); i++)
	{
		window.draw(m_vecSprits[i]);
	}

	//draw the score board
	m_scoreBoard.draw(window);
}

//check if board is open
bool Board::isOpen() const{

    return m_boardOpen;
}


//time calculation
void Board::timeCalculation()
{
	m_scoreBoard.timeCalculation();

	if (m_scoreBoard.timeIsOver())
	{
		m_boardOpen = false;
	}
}