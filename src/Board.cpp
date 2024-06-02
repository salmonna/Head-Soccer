
#pragma once
#include "Board.h"
#include "Resources.h"
#include <fstream>
#include "FileException.h"


// Constructor for the Board class
Board::Board(std::vector<sf::Texture>& texturs):m_boardOpen(true)
{
    m_backGroundStadium.setTexture(texturs[0]);
}

//=============================================== respond =======================================//

// Method to check if a given location corresponds to a stick
void Board::respond(sf::Vector2f loc) {

    
}

//=============================================== draw =======================================//

// Method to draw all sticks in the window
void Board::draw(sf::RenderWindow& window) {
   
    window.draw(m_backGroundStadium);
    m_goal.draw(window);
}

//check if board is open
bool Board::isOpen() const{

    return m_boardOpen;
}
