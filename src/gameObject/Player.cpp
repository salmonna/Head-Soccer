#include "gameObject/Player.h"

Player::Player()
{
}

//-----------------------------------------------------------------------------
// Reset to default position if not jumping
void Player::resetToPosition(sf::Sprite& sprite, sf::Vector2f basePosition,sf::Vector2f startPos, int numOfJump) {

	sf::IntRect characterRect(int(startPos.x) + numOfJump, int(startPos.y), 80, 90); // Assuming each character is 32x32 pixels
	// Set the texture rectangle to the character's position and size on the sprite sheet
	sprite.setTextureRect(characterRect);
	sprite.setPosition(basePosition.x , basePosition.y);
}
//-----------------------------------------------------------------------------
void Player::deactivatePower(b2Body * body,sf::Sprite& sprite ,sf::Color PlayerColor, bool& powerOnPlayer) {
	// Deactivate the power
	powerOnPlayer = false;
	sprite.setColor(PlayerColor);
	body->SetAwake(true);
	// Check if the Player's Y position is greater than 900.f
	if (sprite.getPosition().y > 900.f) {
		// Adjust position if necessary
		b2Vec2 currentPosition = body->GetPosition();
		currentPosition.y = 26.f; // Move the body to the desired Y position

		// Update the body's position and fix the power-related sensor issue
		body->SetTransform(currentPosition, body->GetAngle());
	}
}