
#pragma once
#include "Board.h"
#include "Resources.h"
#include <fstream>
#include "FileException.h"


// Constructor for the Board class
Board::Board(std::vector<sf::Texture>& texturs):m_boardOpen(true),m_jump(0),m_pos(0)
{

	for (int i = 0; i < texturs.size(); i++)
	{
		auto sprite = sf::Sprite(texturs[i]);
		m_vecSprits.push_back(sprite);
	}
	m_vecSprits[1].setPosition(-40,630);
	m_vecSprits[1].scale(0.6,0.6);

	// Define the rectangle to select the character from the sprite sheet
	sf::IntRect characterRect(160,1,63,103); // Assuming each character is 32x32 pixels

	// Set the texture rectangle to the character's position and size on the sprite sheet
	m_vecSprits[2].setTextureRect(characterRect);
	m_vecSprits[2].setPosition(272, 832);
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

	float sec = m_moveClock.getElapsedTime().asMilliseconds();
	if (150 < sec)
	{
		if (m_jump > 600)
		{
			m_jump = 0;
			m_pos = 0;
		}
		else
		{
			m_jump += 115;
			m_pos += 10;
		}
		sf::IntRect characterRect(160 + m_jump, 1, 63, 103); // Assuming each character is 32x32 pixels

		// Set the texture rectangle to the character's position and size on the sprite sheet
		m_vecSprits[2].setTextureRect(characterRect);
		m_vecSprits[2].setPosition(272+ m_pos, 700-m_pos);

		m_moveClock = sf::Clock();
		
	}
}

//check if board is open
bool Board::isOpen() const{

    return m_boardOpen;
}
