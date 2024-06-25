
#include "gameState/Menu.h"
#include <iostream>
#include "Resources.h"
#include "button/QuitButton.h"
#include "button/PlayButton.h"
#include "button/Setting.h"
#include "button/TutorialButton.h"
#include "Command/SwichScreen.h"
#include "Command/Command.h"

//menu constractor initilize his members
Menu::Menu(Controller* controller, GameModeSelection * gameModeState, sf::RenderWindow * window)
{

	std::vector<sf::Texture>& texture = Resources::getInstance().getMenuTexture();
	m_Stage.setTexture(texture[4]);

	////put all the button into one vector
	//m_buttons.push_back(std::make_unique<PlayButton>(texturs[0], gameModeState));
	//m_buttons.push_back(std::make_unique<QuitButton>(texturs[1], window));
	//m_buttons.push_back(std::make_unique<Setting>(texturs[2]));
	//m_buttons.push_back(std::make_unique<TutorialButton>(texturs[3]));
	// 
	//std::unique_ptr<Command> command = std::make_unique<SwichScreen>(gameModeState, controller);
	m_buttons.push_back(std::make_unique<Button>(std::move(std::make_unique<SwichScreen>(gameModeState, controller)), texture[0], sf::Vector2f(100.f, 100.f))); //playButton



};

//check if there is a click on one of the menu buttons
void Menu::respond(sf::Vector2f pressed) {
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
void Menu::draw(sf::RenderWindow& window) const{

	window.draw(m_Stage);

	for (int i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i]->draw(window);
	}
}




