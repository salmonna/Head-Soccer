#pragma once
#include "BaseButton.h"
#include "gameState/GameState.h"
#include "gameState/Board.h"
#include "gameState/SelectTeam.h"

class StartButton : public BaseButton
{
public:
	StartButton(Board* boardState, SelectTeam* selectTeam);
	virtual ~StartButton();


    // Method to simulate clicking the button
    virtual GameState* click() override;

    // Method to display button information
    virtual void draw(sf::RenderWindow& window) const override;

    // Method to check button position
    virtual bool contains(sf::Vector2f position) const override;

private:

    GameState* m_boardState;
    SelectTeam* m_selectTeam;

    sf::Sprite m_start;
};



