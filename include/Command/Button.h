#pragma once
#include "Command.h"
#include <SFML/Graphics.hpp>

class Button
{
public:
	Button(std::unique_ptr<Command> command, sf::Texture & texture, sf::Vector2f position);

	void draw(sf::RenderWindow& window) const;
	void respond();
	bool contains(sf::Vector2f position) const;
	void execute();
	void scale(sf::Vector2f size);
	bool isScaled();
	sf::Vector2f getOrignalSize();

	~Button();

private:
	std::unique_ptr<Command> m_command;
	sf::Sprite m_sprite;
	bool m_isScaled;

	sf::Vector2f m_orignalScale;
};
