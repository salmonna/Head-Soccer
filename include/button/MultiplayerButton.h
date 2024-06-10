

#pragma once
#include "BaseButton.h"
#include <SFML/Graphics.hpp>


class MultiplayerButton :public BaseButton
{
public:
    MultiplayerButton(sf::Texture& texture);

    // Method to simulate clicking the button
    virtual bool click() override;

    // Method to display button information
    virtual void draw(sf::RenderWindow& window) const override;

    // Method to check button position
    virtual bool contains(sf::Vector2f position) const override;

    ~MultiplayerButton() = default;

private:
    sf::Sprite m_multiplayer;
};

