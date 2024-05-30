
#include "Menu.h"
#include <iostream>
#include "Resources.h"

//menu constractor initilize his members
Menu::Menu(std::vector<sf::Texture>& texturs):m_menuOpen(true){

};

//check if there is a click on one of the menu buttons
void Menu::respond(sf::Vector2f mousePressed) {

}

//draw
void Menu::draw(sf::RenderWindow& window) const{

}

//return menu open
bool Menu::isOpen() const {
	return m_menuOpen;
}

