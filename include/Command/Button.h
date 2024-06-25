#pragma once
#include "Command.h"
#include <SFML/Graphics.hpp>

class Button
{
public:
	Button(std::unique_ptr<Command> command, sf::Texture & texture, sf::Vector2f position);

	void draw(sf::RenderWindow& window) const;
	bool contains(sf::Vector2f position) const;
	void execute();

	~Button();

private:
	std::unique_ptr<Command> m_command;
	sf::Sprite m_sprite;
};
