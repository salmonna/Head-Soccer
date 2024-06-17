#pragma once
#include "Window.h"

class Power
{
public:
	Power(sf::Vector2f pos);

	virtual void draw(sf::RenderWindow& window) const = 0;
	void drawAura(sf::RenderWindow& window, sf::Vector2f position);
	sf::Sprite& getSprite();
	void drawProcess(sf::RenderWindow& window);
	bool isProcessFull();

	virtual ~Power() = default;

private:
	sf::Sprite m_auraSprite;
	sf::Clock m_clock;
	std::vector<sf::Sprite> m_progressSprite;
	int m_progress;
};



