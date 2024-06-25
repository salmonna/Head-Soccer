#include "Command/Button.h"


Button::Button(Command * command, sf::Texture& texture) :m_command(command)
{
	m_sprite.setTexture(texture);
}


void Button::draw(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}
Button::~Button()
{


}