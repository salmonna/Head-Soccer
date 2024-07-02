
#include "gameState/Menu.h"
#include <iostream>
#include "Resources.h"
#include "Command/SwichScreen.h"
#include "Command/Command.h"
#include "Command/Quit.h"
#include "SoundControl.h"
#include "Command/Sound.h"


//menu constractor initilize his members
Menu::Menu(Controller* controller, Tutorial* tutorial, GameModeSelection * gameModeState, sf::RenderWindow * window): m_isSongPlayed(false)
{

	std::vector<sf::Texture>& texture = Resources::getInstance().getMenuTexture();
	m_Stage.setTexture(texture[4]);

	m_buttons.push_back(std::make_unique<Button>(std::move(std::make_unique<SwichScreen>(gameModeState, controller)), texture[0], sf::Vector2f(750.f, 300.f))); //playButton
	m_buttons.push_back(std::make_unique<Button>(std::move(std::make_unique<SwichScreen>(tutorial, controller)), texture[3], sf::Vector2f(750.f, 450.f))); //tutorial Button
	m_buttons.push_back(std::make_unique<Button>(std::move(std::make_unique<Quit>(window)), texture[1], sf::Vector2f(750.f, 600.f))); //exit Button

	m_buttons.push_back(std::make_unique<Button>(std::move(std::make_unique<Sound>(SoundControl::getInstance().getIntroSong())), texture[10], sf::Vector2f(0.f, 0.f)));


	sf::Sound& song = SoundControl::getInstance().getIntroSong();
	song.play();
	song.setLoop(true);
	
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