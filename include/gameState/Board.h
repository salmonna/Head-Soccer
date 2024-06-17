
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Window.h"
#include "gameObject/GameObject.h"
#include "gameObject/ScoreBoard.h"
#include "gameObject/Goal.h"
#include "gameObject/MovingObject.h"
#include "gameObject/Player.h"
//#include "Client.h"
#include "GameState.h"
#include "gameState/GameResults.h"
#include "Menu.h"
#include "Pause.h"
//class Pause;


#include "gameObject/ComputerPlayer.h"

class Board : public GameState
{
public:
	Board(Menu * menu, GameResults * gameResults);
	virtual void respond(sf::Vector2f pressed) override;
	void moveAd();
	virtual void draw(sf::RenderWindow& window) const override;
	void drawGameObjects(sf::RenderWindow& window) const;
	template <typename FwdIt, typename Fn>
	void for_each_pair(FwdIt begin, FwdIt end, Fn fn);
	bool collide(GameObject& a, GameObject& b);
	void createMovingObjects(const std::vector<std::string> & objectNames);
	void createStaticObjects(const std::vector<std::string>& objectNames);

	virtual GameState* handleEvents() override;
	void reset();
	~Board() = default;

private:

	void updateScoreBar();

	std::vector<std::shared_ptr<MovingObject>> m_movingObject;
	std::vector<std::shared_ptr<GameObject>> m_gameObject;
	std::vector<std::shared_ptr<StaticObject>> m_staticObject;

	bool m_goalSign;

	ScoreBoard m_scoreBoard;

	GameResults * m_gameResults;
	//Pause  m_pause;
	GameState * m_gameState;
	
	//Client m_client;
	//game objects vector


	sf::Clock m_clock;
	std::vector<std::shared_ptr<GameObject>> m_collidingObject;
	std::vector<std::unique_ptr<BaseButton>> m_buttons;


	std::vector<sf::Sprite> m_backGroundStadium;
	bool m_pressedOnPause;
	sf::Sprite m_goalSprite;

};


