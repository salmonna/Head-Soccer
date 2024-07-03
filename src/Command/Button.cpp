#include "Command/Button.h"
//--------------------------------------------------------------------------------------
// Constructor: Initializes the button with a command, texture, and position
Button::Button(std::unique_ptr<Command> command, sf::Texture& texture, sf::Vector2f position) :m_command(std::move(command)), m_isScaled(false)
{
	m_sprite.setTexture(texture);
	auto width = m_sprite.getGlobalBounds().width;
	auto height = m_sprite.getGlobalBounds().height;

	m_sprite.setOrigin(width / 2, height / 2);
	m_sprite.setPosition(position);

	m_orignalScale = m_sprite.getScale();
}

//--------------------------------------------------------------------------------------
// Draw the button on the given window
void Button::draw(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}

//--------------------------------------------------------------------------------------
// Respond to mouse movement to scale the button if hovered over
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
//--------------------------------------------------------------------------------------
// Check if the button contains the given position
bool Button::contains(sf::Vector2f position) const
{	
	sf::Vector2f newPos = m_sprite.getTransform().getInverse().transformPoint(position);
	return m_sprite.getLocalBounds().contains(newPos);
}
//--------------------------------------------------------------------------------------
// Execute the command associated with the button
void Button::execute()
{
	m_command->execute();
}
//--------------------------------------------------------------------------------------
// Scale the button sprite to the given size
void Button::scale(sf::Vector2f size) {

	m_sprite.setScale(size);

	if (size == m_orignalScale) {
		m_isScaled = false;
		return;
	}
	m_isScaled = true;
}
//--------------------------------------------------------------------------------------
// Check if the button is currently scaled
bool Button::isScaled() {

	return m_isScaled;
}
//--------------------------------------------------------------------------------------
// Get the original size of the button
sf::Vector2f Button::getOrignalSize() {
	return m_orignalScale;
}
//--------------------------------------------------------------------------------------
Button::~Button()
{


}