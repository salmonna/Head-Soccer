#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.h"


class GameResults: public GameState
{
public:
	GameResults();

	virtual void draw(sf::RenderWindow& window) const override;
	virtual void respond(sf::Vector2f mousePressed) override;
	virtual GameState* handleEvents() override;

	~GameResults() = default;

private:
	sf::Sprite m_sprite;
};