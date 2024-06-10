

#pragma once
#include "BaseButton.h"
#include <SFML/Graphics.hpp>

class PlayButton:public BaseButton
{
public:
	PlayButton(sf::Texture& texturs);

    // Method to simulate clicking the button
    virtual bool click() override;

    // Method to display button information
    virtual void draw(sf::RenderWindow& window) const override;

    // Method to check button position
    virtual bool contains(sf::Vector2f position) const override;

	~PlayButton() = default;

private:

    bool m_playPressed;

    sf::Sprite m_play;
};

