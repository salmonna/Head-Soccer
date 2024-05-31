
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class BaseButton {

public:

    // Method to simulate clicking the button
    virtual bool click() const = 0;

    // Method to display button information
    virtual void draw(sf::RenderWindow& window) const = 0;

    // Method to check button position
    virtual bool contains(sf::Vector2f position) const = 0;

    virtual ~BaseButton() = default;
};