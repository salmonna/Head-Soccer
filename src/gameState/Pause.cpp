#pragma once
#include "GameState\Pause.h"
#include "Command/SwichScreen.h"
#include "Command/Command.h"
#include "Resources.h"
#include "SoundControl.h"
#include "Command/Sound.h"

//---------------------------------------------------------------------
Pause::Pause(Controller* controller, Menu * menuState, Board * boardState):
m_boardState(boardState)
{

	std::vector<sf::Texture> & texture = Resources::getInstance().getPauseTexture();
	std::vector<sf::Texture>& tex = Resources::getInstance().getMenuTexture();

	m_buttons.push_back(std::make_unique<Button>(std::move(std::make_unique<SwichScreen>(boardState, controller)), texture[1], sf::Vector2f(900.f, 395.f))); //Resume Button
	m_buttons.push_back(std::make_unique<Button>(std::move(std::make_unique<Sound>(SoundControl::getInstance().getCrowd())), tex[10], sf::Vector2f(900.f, 545.f))); // sound button
	m_buttons.push_back(std::make_unique<Button>(std::move(std::make_unique<SwichScreen>(menuState, controller)), texture[2], sf::Vector2f(900.f, 695.f))); //exit to menu Button


}

//---------------------------------------------------------------------
//check if there is a click on one of the menu buttons
void Pause::respond(sf::Vector2f pressed) {
	//respond to the buttons pressed
	for (int i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i]->respond();

		if (m_buttons[i]->contains(pressed)) {

			if (i == 2) //exit to menu
			{
				m_boardState->reset();
				ScoreBoard::getInstance().reset();
				Resources::getInstance().resetPlayerOrder();
				SoundControl::getInstance().getCrowd().pause();
				SoundControl::getInstance().getIntroSong().play();
			}

			m_buttons[i]->execute();
			return;
		}
	}
}
//---------------------------------------------------------------------
//draw
void Pause::draw(sf::RenderWindow& window) const {

	m_boardState->drawGameObjects(window);

	for (int i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i]->draw(window);

	}
}

