

#pragma once
#include "Resources.h"
#include "FileException.h"
#include <iostream>

//constractor of resources file are loading files
Resources::Resources(){

	std::vector<std::string> fileNames{"Play.png","Quit.png","Setting.png", "Tutorial.png" ,"Stage.png"};
	loadFromFile(fileNames,m_menuTexture);

	std::vector<std::string> boardFileNames{ "Stadium.png", "Goal - Side.png" }; //"Goal - Back.png" //, ,"Goal - Top.png" };
	loadFromFile(boardFileNames, m_boardTexture);


	std::vector<std::string> ScoreBoardfileNames{ "ScoreBoard.png"};
	loadFromFile(ScoreBoardfileNames, m_scoreBoardTexture);

	//if (!m_font.loadFromFile("Font.otf"))
	//{
	//	throw FileException("Font file not load!");
	//}

}

//loadFromFile file function
void Resources::loadFromFile(std::vector<std::string> fileNames, std::vector<sf::Texture>& textures) {

	sf::Texture texture;
	for (int i = 0; i < fileNames.size(); i++)
	{
		if (!texture.loadFromFile(fileNames[i])) {
			throw FileException("textur file not load!");
		}
		textures.push_back(texture);
	}
}

//getMenuTexture

std::vector<sf::Texture>& Resources::getMenuTexture() {

	return m_menuTexture;
}
//getBoardTexture
std::vector<sf::Texture>& Resources::getBoardTexture() {

	return m_boardTexture;
}
//gameResultsTexture
std::vector<sf::Texture>& Resources::gameResultsTexture() {

	return m_gameResultsTexture;
}


//gameResultsTexture
std::vector<sf::Texture>& Resources::getScoreBoardTexture() {

	return m_scoreBoardTexture;
}

//getFont
sf::Font & Resources::getFont() {

	return m_font;
}
	

