#pragma once
#include "Resources.h"
#include "StaticObject.h"


class Goal : public StaticObject
{
public:
	Goal();
	
	virtual void draw(sf::RenderWindow& window) override;
	void setRightGoal();

	virtual ~Goal() = default;

private:
	std::vector<sf::Sprite> m_goalSprite;
};
