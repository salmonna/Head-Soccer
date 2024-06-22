#pragma once
#include <SFML/Graphics.hpp>



class Window
{
public:
	Window();

	void open();
	bool isOpen();
	void eventFunc();
	void clear();
	void close();
	void display();


	sf::RenderWindow& getWindow();
	sf::Vector2f getMousePressed();
	int getKeyPressed();

	~Window() {
	
	};


private:
	sf::RenderWindow m_window;
	sf::Vector2f m_mousePressed;
	unsigned int m_keyPressed;

	void checkMouseReleased(sf::Event event);
};