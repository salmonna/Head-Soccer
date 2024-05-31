#pragma once
#include "Window.h"
#include "BaseButton.h"
#include <vector>
#include <memory>

class Menu
{
public:
	Menu(std::vector<sf::Texture>& texturs);

	void draw(sf::RenderWindow& window) const;
	void respond(sf::Vector2f mousePressed);
	bool isOpen() const;


private:

	bool m_menuOpen;
	
	std::vector<std::unique_ptr<BaseButton>> m_buttons;

	sf::Sprite m_Stage;
};

