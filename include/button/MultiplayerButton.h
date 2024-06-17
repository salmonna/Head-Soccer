

#pragma once
#include "BaseButton.h"
#include <SFML/Graphics.hpp>
#include "gameState/GameState.h"
#include "gameState/SelectTeam.h"
#include "gameState/Board.h"
#include "gameState/SelectTeam.h"

class MultiplayerButton :public BaseButton
{
public:
    MultiplayerButton(sf::Texture& texture, Board* boardState, SelectTeam* selectTeam);

    // Method to simulate clicking the button
    virtual GameState * click() override;

    // Method to display button information
    virtual void draw(sf::RenderWindow& window) const override;

    // Method to check button position
    virtual bool contains(sf::Vector2f position) const override;

    ~MultiplayerButton() = default;

private:

    Board* m_boardState;
    SelectTeam* m_selectTeam;
    sf::Sprite m_multiplayer;
};

