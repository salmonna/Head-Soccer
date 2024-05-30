#pragma once
#include "Window.h"

class Menu
{
public:
	Menu(std::vector<sf::Texture>& texturs);

	void draw(sf::RenderWindow& window) const;
	void respond(sf::Vector2f mousePressed);
	bool isOpen() const;


private:

	bool m_menuOpen;

};

