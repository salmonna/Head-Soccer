
#pragma once
#include "BaseButton.h"
#include <SFML/Graphics.hpp>
#include "gameState/GameState.h"
#include "gameState/Board.h"

class OnlineButton :public BaseButton
{
public:
    OnlineButton(sf::Texture& texture, Board* boardState);

    // Method to simulate clicking the button
    virtual GameState* click() override;

    // Method to display button information
    virtual void draw(sf::RenderWindow& window) const override;

    // Method to check button position
    virtual bool contains(sf::Vector2f position) const override;

    ~OnlineButton() = default;

private:

    Board* m_boardState;
    sf::Sprite m_online;
};

