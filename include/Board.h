
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Window.h"
#include "GameObject.h"
#include "ScoreBoard.h"
#include "Goal.h"

#include "MovingObject.h"


class Board
{
public:
	Board(std::vector<sf::Texture>& texturs);


	void respond(int keyPressed);
	void draw(sf::RenderWindow& window);

	
	bool isOpen() const;

	~Board() = default;

private:

	void timeCalculation();


	std::vector<std::unique_ptr<MovingObject>> m_movingObject;


	bool m_boardOpen;

	//game objects vector
	std::vector<std::unique_ptr<GameObject>> m_gameObjects;



	sf::Sprite m_backGroundStadium;

	Goal m_leftGoal;
	Goal m_rightGoal;

	sf::Clock m_moveClock;

};



