


#pragma once
#include "BaseButton.h"
#include <SFML/Graphics.hpp>
#include "gameState/GameState.h"
#include "gameState/GameModeSelection.h"

class ReplayButton :public BaseButton
{
public:
    ReplayButton(sf::Texture& texture, GameModeSelection* menuState);

    // Method to simulate clicking the button
    virtual GameState* click() override;

    // Method to display button information
    virtual void draw(sf::RenderWindow& window) const override;

    // Method to check button position
    virtual bool contains(sf::Vector2f position) const override;

    ~ReplayButton() = default;

private:

    GameModeSelection* m_menuState;
    sf::Sprite m_replayButton;
};

