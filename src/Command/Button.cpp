#include "Command/Button.h"


Button::Button(std::unique_ptr<Command> command, sf::Texture& texture, sf::Vector2f position) :m_command(std::move(command)), m_isScaled(false)
{
	m_sprite.setTexture(texture);
	m_sprite.setPosition(position);
	m_orignalScale = m_sprite.getScale();
	//m_sprite.setOrigin(m_orignalScale.x/2, m_orignalScale.y/2);
	
}


void Button::draw(sf::RenderWindow& window) 
{
	sf::Vector2i mouseMove = sf::Mouse::getPosition(window);

	if (contains(sf::Vector2f(float(mouseMove.x), float(mouseMove.y)))) {

		if (!isScaled()) {
			scale(sf::Vector2f(1.15f, 1.15f));
		}
	}
	else if (isScaled()) {

		scale(getOrignalSize());
	}

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