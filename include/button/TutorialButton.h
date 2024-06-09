

#pragma once
#include "BaseButton.h"
#include <SFML/Graphics.hpp>

class TutorialButton : public BaseButton
{
public:
    TutorialButton(sf::Texture& texture);

    // Method to simulate clicking the button
    virtual bool click() override;

    // Method to display button information
    virtual void draw(sf::RenderWindow& window) const override;

    // Method to check button position
    virtual bool contains(sf::Vector2f position) const override;

    std::string getText() const;

    ~TutorialButton() = default;

private:

    sf::Sprite m_tutorial;
    sf::Text m_tutorialText;

    bool m_buttonPressed;
};



