#pragma once
#include "Window.h"

class Power
{
public:
	Power();

	virtual void draw(sf::RenderWindow& window) const = 0;
	void drawProcess(sf::RenderWindow& window) const;
	void drawAura(sf::RenderWindow& window, sf::Vector2f position);
	sf::Sprite& getSprite();

	~Power() = default;

private:

	sf::Sprite m_progressSprite;
	sf::Sprite m_auraSprite;
};



