#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include <iostream>


class GameResults: public GameState
{
public:
	GameResults();

	virtual void draw(sf::RenderWindow& window) const override;
	virtual void respond(sf::Vector2f mousePressed) override;
	virtual GameState* handleEvents() override;

	~GameResults() {
		std::cout << "D-tor game results dynmic" << std::endl;
	};

private:
	sf::Sprite m_sprite;
};