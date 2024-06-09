
#pragma once
#include "Board.h"
#include "Resources.h"
#include <fstream>
#include "FileException.h"
#include "gameObject/Player.h"
#include "gameObject/StaticObject.h"
#include "Keyboard.h"
#include "gameObject/Ball.h"
#include "CollisionHandling.h"


// Constructor for the Board class
Board::Board(std::vector<sf::Texture>& texturs):m_boardOpen(true), m_scoreBoard(180)
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


	Keyboard keyPlayer1(sf::Keyboard::Space, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up,sf::Keyboard::Down);
	Keyboard keyPlayer2(sf::Keyboard::Z, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, sf::Keyboard::S);
	m_movingObject.push_back(std::make_shared<Player>(true, keyPlayer1));
	m_movingObject.push_back(std::make_shared<Player>(false, keyPlayer2));
	//m_client.sendData(*m_movingObject[1]);
	m_gameObject.push_back(m_movingObject[0]);
	m_gameObject.push_back(m_movingObject[1]);
	

	//update ball
	auto ball = std::make_shared<Ball>();
	m_movingObject.push_back(ball);
	m_gameObject.push_back(ball);


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
		//if (i == 1)
		//{
		//	//othere player
		//	//m_client.receiveData(*m_movingObject[i]);
		//}
		//else if(i == 0)
		//{
		//	m_movingObject[i]->move(keyPressed);
		//	//m_client.sendData(*m_movingObject[i]);
		//}
		//else
		//{
		//	
		//}
	}

	for_each_pair(m_gameObject.begin(), m_gameObject.end(), [&](auto& a, auto& b) {
		if (collide(*a, *b))
		{
			processCollision(*a, *b);

			if ((typeid(*a) == typeid(Goal) && typeid(*b) == typeid(Ball)))
			{
				Ball& ballObject = dynamic_cast<Ball&>(*b);

				if (&(dynamic_cast<Goal&>(*a)) == &(dynamic_cast<Goal&>(*m_staticObject[0]))) //check was goal
				{
					m_scoreBoard.updateScore(0, 1);
				}
				else
				{
					m_scoreBoard.updateScore(1, 0);
				}

				
				
				ballObject.setBallVelocity(sf::Vector2f(5.f, -10.f));
				ballObject.setPosition(sf::Vector2f(900.0f, 494.0f));
			}		
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

//bool Board::collide(GameObject& a, GameObject& b)
//{
//
//	sf::FloatRect otherBounds = b.getSprite().getGlobalBounds();
//
//
//	// Convert the corners of the other bounding box to the local space of this sprite
//	sf::Vector2f topLeft = a.getSprite().getTransform().getInverse().transformPoint(sf::Vector2f(otherBounds.left, otherBounds.top));
//	sf::Vector2f topRight = a.getSprite().getTransform().getInverse().transformPoint(sf::Vector2f(otherBounds.left + otherBounds.width, otherBounds.top));
//	sf::Vector2f bottomLeft = a.getSprite().getTransform().getInverse().transformPoint(sf::Vector2f(otherBounds.left, otherBounds.top + otherBounds.height));
//	sf::Vector2f bottomRight = a.getSprite().getTransform().getInverse().transformPoint(sf::Vector2f(otherBounds.left + otherBounds.width, otherBounds.top + otherBounds.height));
//
//	// Check if any of the corners are within the local bounds of this sprite
//	sf::FloatRect localBounds = a.getSprite().getLocalBounds();
//	return localBounds.contains(topLeft) || localBounds.contains(topRight) ||
//		localBounds.contains(bottomLeft) || localBounds.contains(bottomRight);
//
//}

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