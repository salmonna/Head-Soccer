#pragma once
#include "Window.h"
#include "button/BaseButton.h"
#include <vector>
#include <memory>

class Menu
{
public:
	Menu(std::vector<sf::Texture>& texturs);

	void draw(sf::RenderWindow& window) const;
	void respond(sf::Vector2f mousePressed);
	bool isOpen() const;

	bool isExit() const;

private:

	bool m_menuOpen;
	bool m_exit;
	bool m_play;

	std::vector<std::unique_ptr<BaseButton>> m_buttons;
	std::vector<bool> m_buttonPressed;

	sf::Sprite m_Stage;
};

