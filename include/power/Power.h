#pragma once
#include "Window.h"

class Power
{
public:
	Power();

	virtual void draw(sf::RenderWindow& window) const = 0;
	void drawProcess(sf::RenderWindow& window) const;


	~Power() = default;

private:

	sf::Sprite m_progressSprite;

};



