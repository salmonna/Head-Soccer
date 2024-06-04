
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Window.h"
#include "GameObject.h"
#include "ScoreBoard.h"
#include "Goal.h"
#include "RightGoal.h"
#include <memory>


class Board
{
public:
	Board(std::vector<sf::Texture>& texturs);

	void respond(sf::Vector2f loc);
	void draw(sf::RenderWindow & window);
	
	bool isOpen() const;

	~Board() = default;

private:

	void timeCalculation();

	bool m_boardOpen;

	//game objects vector
	std::vector<std::unique_ptr<GameObject>> m_gameObjects;

	std::vector<sf::Sprite> m_vecSprits;
	//ScoreBoard m_scoreBoard;

	sf::Sprite m_backGroundStadium;
	std::vector<std::unique_ptr<Goal>> m_goalObjects;
};



