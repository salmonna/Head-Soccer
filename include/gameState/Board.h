
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Window.h"
#include "gameObject/GameObject.h"
#include "gameObject/ScoreBoard.h"
#include "gameObject/Goal.h"
#include "gameObject/MovingObject.h"
#include "gameObject/Player.h"
#include "Client.h"
#include "GameState.h"

#include "gameObject/ComputerPlayer.h"

class Board : public GameState
{
public:
	Board();
	virtual void respond(sf::Vector2f pressed) override;
	virtual void draw(sf::RenderWindow& window) const override;

	template <typename FwdIt, typename Fn>
	void for_each_pair(FwdIt begin, FwdIt end, Fn fn);
	bool collide(GameObject& a, GameObject& b);
	bool isOpen() const;

	virtual GameState* handleEvents() override;


	~Board() = default;

private:

	void timeCalculation();
	void updateScoreBar();

	std::vector<std::shared_ptr<MovingObject>> m_movingObject;
	std::vector<std::shared_ptr<GameObject>> m_gameObject;
	std::vector<std::shared_ptr<StaticObject>> m_staticObject;

	bool m_boardOpen;
	ScoreBoard m_scoreBoard;

	//Client m_client;
	//game objects vector

	std::vector<std::shared_ptr<GameObject>> m_collidingObject;

	sf::Sprite m_backGroundStadium;
	
};



