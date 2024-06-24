#pragma once
#include "gameObject/Goal.h"
#include "Factory/StaticFactory.h"

class GoalSide : public Goal
{
	public:
		GoalSide(int x, int y, bool needScale);
		~GoalSide();

		virtual void draw(sf::RenderWindow& window)const override;
		virtual sf::Sprite& getSprite()override;

	private:
		sf::Sprite m_sprite;


		static bool m_registeritLeftInsideGoalSide;
		static bool m_registeritRightInsideGoalSide;
		static bool m_registeritLeftOutsideGoalSide;
		static bool m_registeriiRightOutsideGoalSide;
};


