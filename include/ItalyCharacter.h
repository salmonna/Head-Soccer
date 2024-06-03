

#pragma once
#include <SFML/Graphics.hpp>


class ItalyCharacter
{
public:
	ItalyCharacter(sf::Texture& texture);

	void draw(sf::RenderWindow& window);

	void move();

	~ItalyCharacter();

private:
	
	sf::Sprite m_sprite;
	sf::Clock m_moveClock;
};

