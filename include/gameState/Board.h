
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Window.h"
#include "gameObject/GameObject.h"
#include "gameObject/ScoreBoard.h"
#include "gameObject/Goal.h"
#include "gameObject/MovingObject.h"
#include "gameObject/UserPlayer.h"
#include "GameState.h"
#include "gameState/GameResults.h"
#include "Menu.h"
#include "Pause.h"
#include "Box2d.h"
#include "gameObject/ComputerPlayer.h"
#include "MovePlayerState/BaseMovePlayerState.h"
#include "MovePlayerState/LeftMoveState.h"
#include "MovePlayerState/RightMoveState.h"
#include "MovePlayerState/StandPlayerState.h"
#include "Command/Button.h"

class Controller;

class Board : public GameState
{
public:
	Board(Controller * controller, Pause * pause, GameResults * gameResults);
	virtual void respond(sf::Vector2f pressed) override;
	void moveAd();
	virtual void draw(sf::RenderWindow& window) const override;
	void drawGameObjects(sf::RenderWindow& window) const;
	template <typename FwdIt, typename Fn>
	void for_each_pair(FwdIt begin, FwdIt end, Fn fn);
	bool collide(GameObject& a, GameObject& b);
	void createMovingObjects(const std::vector<std::string> & objectNames);
	void createStaticObjects(const std::vector<std::string>& objectNames);

	void reset();
	~Board() = default;

private:

	void handleScoreBoard();

	std::vector<std::shared_ptr<MovingObject>> m_movingObject;
	std::vector<std::shared_ptr<GameObject>> m_gameObject;
	std::vector<std::shared_ptr<StaticObject>> m_staticObject;

	GameResults * m_gameResults;
	
	//Client m_client;
	//game objects vector

	Controller* m_controllerPtr;
	std::vector<std::shared_ptr<GameObject>> m_collidingObject;
 	std::vector<std::unique_ptr<Button>> m_buttons;
	std::vector<sf::Sprite> m_backGroundStadium;
	bool m_pressedOnPause;
};


