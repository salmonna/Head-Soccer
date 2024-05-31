
#include "Menu.h"
#include <iostream>
#include "Resources.h"
#include "QuitButton.h"
#include "PlayButton.h"
#include "Setting.h"
#include "TutorialButton.h"

//menu constractor initilize his members
Menu::Menu(std::vector<sf::Texture>& texturs):m_menuOpen(true){

	m_buttons.push_back(std::make_unique<PlayButton>(texturs[0]));
	m_buttons.push_back(std::make_unique<QuitButton>(texturs[1]));
	m_buttons.push_back(std::make_unique<Setting>(texturs[2]));
	m_buttons.push_back(std::make_unique<TutorialButton>(texturs[3]));

	m_Stage.setTexture(texturs[4]);
};

//check if there is a click on one of the menu buttons
void Menu::respond(sf::Vector2f mousePressed) {
	for (int i = 0; i < m_buttons.size(); i++)
	{
		if (m_buttons[i]->contains(mousePressed)) {
			m_menuOpen = m_buttons[i]->click();
			break;
		}
	}
}

//draw
void Menu::draw(sf::RenderWindow& window) const{

	window.draw(m_Stage);

	for (int i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i]->draw(window);
	}
}

//return menu open
bool Menu::isOpen() const {
	return m_menuOpen;
}
