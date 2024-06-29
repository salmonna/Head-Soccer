#pragma once
#include "gameState/Tutorial.h"
#include "Command/SwichScreen.h"
#include "Command/Command.h"
#include "Resources.h"


Tutorial::Tutorial(Controller* controller, Menu* prevState)
{

	std::vector<sf::Texture>& texture = Resources::getInstance().getMenuTexture();

	m_sprite.setTexture(texture[8]);
	m_buttons.push_back(std::make_unique<Button>(std::move(std::make_unique<SwichScreen>(prevState, controller)), texture[7], sf::Vector2f(0, 0))); //Button 4

}


//check if there is a click on one of the menu buttons
void Tutorial::respond(sf::Vector2f pressed) {
	//respond to the buttons pressed
	for (int i = 0; i < m_buttons.size(); i++)
	{
		if (m_buttons[i]->contains(pressed)) {

			m_buttons[i]->execute();
			return;
		}
	}
}

//draw
void Tutorial::draw(sf::RenderWindow& window) const {


	window.draw(m_sprite);

	for (int i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i]->draw(window);
	}
}

