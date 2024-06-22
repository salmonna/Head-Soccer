#include "power/FirePower.h"


FirePower::FirePower(sf::Vector2f pos) : Power(pos)
{

}


void FirePower::activatePower(sf::Sprite& ball, sf::Sprite& player)
{
	ball.setColor(sf::Color::Red);
}

void FirePower::draw(sf::RenderWindow& window) const
{


}