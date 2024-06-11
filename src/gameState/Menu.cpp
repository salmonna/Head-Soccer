
#include "gameState/Menu.h"
#include <iostream>
#include "Resources.h"
#include "button/QuitButton.h"
#include "button/PlayButton.h"
#include "button/Setting.h"
#include "button/TutorialButton.h"
#include "button/MultiplayerButton.h"
#include "button/PlayerButton.h"

//menu constractor initilize his members
Menu::Menu(Board * boardState , sf::RenderWindow * window):m_gameState(NULL),
m_menuOpen(true),m_exit(false),m_play(false)
{

	std::vector<sf::Texture>& texturs = Resources::getInstance().getMenuTexture();

	//put all the button into one vector
	m_buttons.push_back(std::make_unique<PlayButton>(texturs[0], boardState));
	m_buttons.push_back(std::make_unique<QuitButton>(texturs[1], window));
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
void Menu::respond(sf::Vector2f pressed) {
	//respond to the buttons pressed
	for (int i = 0; i < m_buttons.size(); i++)
	{
		if (m_buttons[i]->contains(pressed)) {
			
			m_gameState = m_buttons[i]->click();
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

	//if (m_buttonPressed[0])
	//{
	//	m_buttons[4]->draw(window);
	//	m_buttons[5]->draw(window);
	//}
}


GameState * Menu::handleEvents()
{
	return m_gameState;
}


//return menu open
bool Menu::isOpen() const {
	return m_menuOpen;
}

//return menu open
bool Menu::isExit() const {
	return m_exit;
}
