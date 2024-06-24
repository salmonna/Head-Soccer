

#pragma once
#include "BaseButton.h"
#include <SFML/Graphics.hpp>
#include "gameState/GameState.h"
#include "gameState/GameModeSelection.h"

class PlayButton:public BaseButton
{
public:
	PlayButton(sf::Texture& texturs, GameModeSelection* GameModeSelectionState);

    // Method to simulate clicking the button
    virtual GameState * click() override;

    // Method to display button information
    virtual void draw(sf::RenderWindow& window) const override;

    // Method to check button position
    virtual bool contains(sf::Vector2f position) const override;

	~PlayButton() = default;

private:
    GameModeSelection* m_gameModeState;

    bool m_playPressed;

    sf::Sprite m_play;
};

