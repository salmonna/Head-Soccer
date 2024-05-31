#pragma once
#include "Setting.h"

Setting::Setting(sf::Texture& texture)
{
	m_setting.setTexture(texture);
	m_setting.setPosition(100, 300);

}


// Method to simulate clicking the button
bool Setting::click() const {
	return true;
}

// Method to display button information
void Setting::draw(sf::RenderWindow& window) const {
	window.draw(m_setting);
}

// Method to check button position
bool Setting::contains(sf::Vector2f position) const {
	return m_setting.getGlobalBounds().contains(position);
}
