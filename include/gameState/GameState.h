#pragma once
#include <SFML/Graphics.hpp>


class GameState
{
public:
	virtual void draw(sf::RenderWindow& window) const  = 0 ;
	virtual void respond(sf::Vector2f Pressed) = 0;
	virtual GameState* prevState() { return this; };

	virtual ~GameState() = default;
private:

};