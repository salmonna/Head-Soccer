#pragma once
#include "Window.h"
#include <iostream>

// Constructor for the Window class.
//----------------------------------------------------------------
Window::Window(){}

// Opens a new window with the specified number of columns and rows.
//----------------------------------------------------------------
void Window::open() {
	m_window.create(sf::VideoMode(1800,1013), "Head Soccer");
	m_window.setFramerateLimit(60);
}

// Checks if the window is open.
//----------------------------------------------------------------
bool Window::isOpen() {
	return m_window.isOpen();
}

// Handles window events such as closing the window.
//----------------------------------------------------------------
void Window::eventFunc() {
	if (auto event = sf::Event{}; m_window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			close();
			exit(EXIT_SUCCESS);
			break;

		case sf::Event::MouseButtonReleased:

			checkMouseReleased(event);
			return ;
		}
	}
	m_mousePressed.x = -1.f;
	m_mousePressed.y = -1.f;
}
//------------------------------------------------------------------//
// checkMouseReleased
void Window::checkMouseReleased(sf::Event event) {

	switch (event.mouseButton.button)
	{
	case sf::Mouse::Button::Left:
		m_mousePressed = sf::Vector2f(m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }));
		return;
	}
	m_mousePressed.x = -1.f;
	m_mousePressed.y = -1.f;
}


// Returns the reference to the window object.
//----------------------------------------------------------------
sf::RenderWindow& Window::getWindow() {
	return  m_window;
}

// Clears the window.
void Window::clear() {
	m_window.clear(sf::Color(128U,128U,128U));
}

// Displays the contents of the window.
//----------------------------------------------------------------
void Window::display() {
	m_window.display();
}

// Closes the window.
//----------------------------------------------------------------
void Window::close() {
	m_window.close();
}

//return mouse position 
//----------------------------------------------------------------
sf::Vector2f Window::getMousePressed() {
	return m_mousePressed;
}

