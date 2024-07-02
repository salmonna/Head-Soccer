#pragma once
#include "gameState/Tutorial.h"
#include "Command/SwichScreen.h"
#include "Command/Command.h"
#include "Resources.h"


Tutorial::Tutorial(Controller* controller, Menu* prevState)
{

	std::vector<sf::Texture>& texture = Resources::getInstance().getMenuTexture();

	m_sprite.push_back(sf::Sprite(Resources::getInstance().getGameModeTexture()[0]));

	for (int i = 0; i < 2; i++)
	{
		auto sprite = sf::Sprite(Resources::getInstance().getMenuTexture()[8 + i]);
		sprite.setPosition(250, 650);
		sprite.scale(0.3f,0.3f);
		m_sprite.push_back(sprite);
	}
	m_sprite[2].setPosition(1150,650);


	m_buttons.push_back(std::make_unique<Button>(std::move(std::make_unique<SwichScreen>(prevState, controller)), texture[7], sf::Vector2f(0, 0))); //Button 4

	tutorialText();

}

void Tutorial::tutorialText()
{

	sf::Font& font = Resources::getInstance().getFont();

	for (int i = 0; i < 3; i++)
	{
		m_tutorialText.push_back(sf::Text());
		m_tutorialText[i].setFont(font);
		m_tutorialText[i].setPosition(120, 100);
		m_tutorialText[i].setCharacterSize(80);
		m_tutorialText[i].setFillColor(sf::Color::Black);
		m_tutorialText[i].setStyle(sf::Text::Bold);

		//Adding an outline to the text
		m_tutorialText[i].setOutlineColor(sf::Color::White);//(135, 206, 250)
		m_tutorialText[i].setOutlineThickness(3);

	}
	m_tutorialText[0].setString("Controls:	Use the Left/A and Right/D arrows to move, Up/W button to jump,\n"
								"				Space/Q button to kick and Down/S button to charge a power shot.\n"
								"Objective:   Score more goals than your opponent within the time limit.\n"
								"Strategy:   Position yourself between the ball and your goal, use power shots strategically.");

	m_tutorialText[1].setString("Left Player");
	m_tutorialText[2].setString("Right Player");
	m_tutorialText[1].setPosition(300, 550);
	m_tutorialText[2].setPosition(1250, 550);

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


	for (int i = 0; i < m_sprite.size(); i++)
	{
		window.draw(m_sprite[i]);
	}

	for (int i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i]->draw(window);
	}

	for (int i = 0; i < m_tutorialText.size(); i++)
	{
		window.draw(m_tutorialText[i]);
	}
}

