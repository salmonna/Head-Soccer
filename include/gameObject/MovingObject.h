
#pragma once
#include  "GameObject.h"


class MovingObject:public GameObject
{
public:
	MovingObject() = default;

	virtual void move(int keyPressed) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual sf::Vector2f getPosition() const = 0;

	//virtual void update(sf::Sprite & ball, sf::Vector2f& velocity, float deltaTime) = 0;
	virtual int getKeypressed() = 0;

	~MovingObject() = default;

private:

};

