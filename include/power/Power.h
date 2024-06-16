#pragma once
#include "Window.h"

class Power
{
public:
	Power(sf::Vector2f pos);

	virtual void draw(sf::RenderWindow& window) const = 0;
	void drawProcess(sf::RenderWindow& window);


	~Power() = default;

private:

	sf::Clock m_clock;
	std::vector<sf::Sprite> m_progressSprite;
	int m_progress;

};



