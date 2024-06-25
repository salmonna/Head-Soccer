#pragma once
#include "Command.h"
#include <SFML/Graphics.hpp>

class Button
{
public:
	Button(Command * command, sf::Texture & texture);

	void draw(sf::RenderWindow& window) const;
	
	~Button();

private:
	std::unique_ptr<Command> m_command;
	sf::Sprite m_sprite;
};
