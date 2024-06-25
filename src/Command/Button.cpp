#include "Command/Button.h"


Button::Button(std::unique_ptr<Command> command, sf::Texture& texture, sf::Vector2f position) :m_command(std::move(command))
{
	m_sprite.setTexture(texture);
	m_sprite.setPosition(position);
}


void Button::draw(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}


bool Button::contains(sf::Vector2f position) const
{
	return m_sprite.getGlobalBounds().contains(position);
}

void Button::execute()
{
	m_command->execute();
}

Button::~Button()
{


}