
#include "gameObject/MovingObject.h"

// Function to convert Box2D coordinates to SFML coordinates
sf::Vector2f MovingObject::B2VecToSFVec(const b2Vec2& vector) {
    return sf::Vector2f(vector.x * SCALE, vector.y * SCALE);
}