#pragma once
#include "ScoreBoard.h"
#include "Resources.h"

ScoreBoard::ScoreBoard()
{

	std::vector<sf::Texture>& texturs = Resources::getInstance().getScoreBoardTexture();
	for (int i = 0; i < texturs.size(); i++)
	{
		auto sprite = sf::Sprite(texturs[i]);
		m_SpriteVec.push_back(sprite);
	}
	float x = 1800 / 2 - m_SpriteVec[0].getScale().x;

	m_SpriteVec[0].setPosition(x, -100);

}


void ScoreBoard::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < m_SpriteVec.size(); i++)
	{
		window.draw(m_SpriteVec[i]);
	}
}