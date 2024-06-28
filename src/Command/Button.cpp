#include "Command/Button.h"


Button::Button(std::unique_ptr<Command> command, sf::Texture& texture, sf::Vector2f position) :m_command(std::move(command)), m_isScaled(false)
{
	m_sprite.setTexture(texture);
	m_sprite.setPosition(position);
	
	m_orignalScale = m_sprite.getScale();
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

void Button::scale(sf::Vector2f size) {

	m_sprite.setScale(size);

	if (size == m_orignalScale) {
		m_isScaled = false;
		return;
	}
	m_isScaled = true;
}

bool Button::isScaled() {

	return m_isScaled;
}

sf::Vector2f Button::getOrignalSize() {
	return m_orignalScale;
}
Button::~Button()
{


}