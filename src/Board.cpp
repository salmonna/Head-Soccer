
#pragma once
#include "Board.h"
#include "Resources.h"
#include <fstream>
#include "FileException.h"
#include "Player.h"

// Constructor for the Board class
Board::Board(std::vector<sf::Texture>& texturs):m_boardOpen(true),m_jump(0),m_pos(0)
{

	for (int i = 0; i < texturs.size()-1; i++)
	{
		auto sprite = sf::Sprite(texturs[i]);
		m_vecSprits.push_back(sprite);
	}
	m_movingObject.push_back(std::make_unique<Player>(texturs[2]));

	m_vecSprits[1].setPosition(-40,630);
	m_vecSprits[1].scale(0.6,0.6);
}

//=============================================== respond =======================================//

// Method to check if a given location corresponds to a stick
void Board::respond(int keyPressed) {

	for (int i = 0; i < m_movingObject.size(); i++)
	{
		m_movingObject[i]->move(keyPressed);
	}
}

//=============================================== draw =======================================//

// Method to draw all sticks in the window
void Board::draw(sf::RenderWindow& window) {
   
	for (int i = 0; i < m_vecSprits.size(); i++)
	{
		window.draw(m_vecSprits[i]);
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
