#include "Command/Button.h"

//400.f / 2, 125.f / 2

Button::Button(std::unique_ptr<Command> command, sf::Texture& texture, sf::Vector2f position) :m_command(std::move(command)), m_isScaled(false)
{
	m_sprite.setTexture(texture);
	auto width = m_sprite.getGlobalBounds().width;
	auto height = m_sprite.getGlobalBounds().height;

	m_sprite.setOrigin(width / 2, height / 2);
	m_sprite.setPosition(position);

	m_orignalScale = m_sprite.getScale();
}


void Button::draw(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}


void Button::respond()
{

	sf::Vector2i mouseMove = sf::Mouse::getPosition();

	if (contains(sf::Vector2f(float(mouseMove.x), float(mouseMove.y)))) {

		if (!isScaled()) {
			scale(sf::Vector2f(1.15f, 1.15f));
		}
	}
	else if (isScaled()) {

		scale(getOrignalSize());
	}

}


bool Button::contains(sf::Vector2f position) const
{	
	sf::Vector2f newPos = m_sprite.getTransform().getInverse().transformPoint(position);
	return m_sprite.getLocalBounds().contains(newPos);
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