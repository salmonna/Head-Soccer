
#include  "GameObject.h"


class MovingObject:public GameObject
{
public:
	MovingObject(int keyPressed) = default;

	virtual void move() = 0;
	virtual void draw(sf::RenderWindow& window) = 0;


	~MovingObject() = default;

private:

};

