#pragma once
#include "Window.h"
#include "MoveBehavior.h"
#include <SFML/Graphics.hpp>

class Power : public MoveBehavior
{
public:
	Power(sf::Vector2f pos);
	
	virtual void draw(sf::RenderWindow& window) const = 0;
	void drawAura(sf::RenderWindow& window, sf::Vector2f position);
	sf::Sprite& getSprite();
	void drawProcess(sf::RenderWindow& window);
	void resetProgress();
	virtual void activatePower(sf::Sprite & ball, sf::Sprite & player) = 0;
	bool isProcessFull();




	virtual ~Power() = default;


private:
	sf::Sprite m_auraSprite;
	sf::Clock m_clock;
	std::vector<sf::Sprite> m_progressSprite;
	int m_progress;
};



