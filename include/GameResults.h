#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.h"


class GameResults 
{
public:
	GameResults(std::vector<sf::Texture>& texturs);

	bool isOpen();
	void draw(sf::RenderWindow& window);
	void respond(sf::Vector2f mouseClick);

	~GameResults() = default;

private:

	bool m_gameResultsOpen;
};