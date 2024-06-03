
#include "Menu.h"
#include <iostream>
#include "Resources.h"
#include "QuitButton.h"
#include "PlayButton.h"
#include "Setting.h"
#include "TutorialButton.h"
#include "MultiplayerButton.h"
#include "PlayerButton.h"

//menu constractor initilize his members
Menu::Menu(std::vector<sf::Texture>& texturs):m_menuOpen(true),m_exit(false),m_play(false){

	//put all the button into one vector
	m_buttons.push_back(std::make_unique<PlayButton>(texturs[0]));
	m_buttons.push_back(std::make_unique<QuitButton>(texturs[1]));
	m_buttons.push_back(std::make_unique<Setting>(texturs[2]));
	m_buttons.push_back(std::make_unique<TutorialButton>(texturs[3]));
	m_buttons.push_back(std::make_unique<MultiplayerButton>(texturs[4]));
	m_buttons.push_back(std::make_unique<PlayerButton>(texturs[5]));

	m_Stage.setTexture(texturs[6]);

	for (int i = 0; i < m_buttons.size(); i++)
	{
		m_buttonPressed.push_back(false);
	}

};

//check if there is a click on one of the menu buttons
void Menu::respond(sf::Vector2f mousePressed) {
	//respond to the buttons pressed
	for (int i = 0; i < m_buttons.size() - 2; i++)
	{
		if (m_buttons[i]->contains(mousePressed)) {
			m_buttonPressed[i] = m_buttons[i]->click();
			if (m_buttonPressed[i] && i == 1)
			{
				m_menuOpen = false;
				m_exit = true;
			}
			break;
		}
	}
	if (m_buttonPressed[0])
	{
		if (m_buttons[4]->contains(mousePressed)) {

			m_menuOpen = false;
		}
		else if (m_buttons[5]->contains(mousePressed)) {
			m_menuOpen = false;
		}
	}
}

//draw
void Menu::draw(sf::RenderWindow& window) const{

	window.draw(m_Stage);

	for (int i = 0; i < m_buttons.size() - 2; i++)
	{
		m_buttons[i]->draw(window);
	}

	if (m_buttonPressed[0])
	{
		m_buttons[4]->draw(window);
		m_buttons[5]->draw(window);
	}
}

//return menu open
bool Menu::isOpen() const {
	return m_menuOpen;
}

//return menu open
bool Menu::isExit() const {
	return m_exit;
}
