
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Window.h"
#include "GameObject.h"
#include "ScoreBoard.h"
#include "Goal.h"
#include "MovingObject.h"
#include "Player.h"


class Board
{
public:
	Board(std::vector<sf::Texture>& texturs);
	void respond(int keyPressed);
	void draw(sf::RenderWindow& window);

	template <typename FwdIt, typename Fn>
	void for_each_pair(FwdIt begin, FwdIt end, Fn fn);

	bool collide(GameObject& a, GameObject& b);

	bool isOpen() const;

	~Board() = default;

private:

	void timeCalculation();

	std::vector<std::shared_ptr<MovingObject>> m_movingObject;

	std::vector<std::shared_ptr<GameObject>> m_gameObject;
	std::vector<std::shared_ptr<StaticObject>> m_staticObject;

	bool m_boardOpen;
	ScoreBoard m_scoreBoard;


	//game objects vector

	std::vector<std::shared_ptr<GameObject>> m_collidingObject;

	sf::Sprite m_backGroundStadium;

};



