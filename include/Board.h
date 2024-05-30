
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Board
{
public:
	Board(std::vector<sf::Texture>& texturs);

	void respond(sf::Vector2f loc);
	void draw(sf::RenderWindow& window);
	
	bool isOpen() const;

	~Board() = default;

private:


	bool m_boardOpen;

	
};



