

#pragma once
#include "Resources.h"
#include "FileException.h"
#include <iostream>

//constractor of resources file are loading files
Resources::Resources(){

	std::vector<std::string> fileNames{"Play.png","Quit.png","Setting.png", "Tutorial.png","Stage.png","Sounds.png","Music.png" };
	loadFromFile(fileNames,m_menuTexture);

	std::vector<std::string> boardFileNames{ "Stadium.png", "Ad Board.png","Goal.png"};
	loadFromFile(boardFileNames, m_boardTexture);

	std::vector<std::string> goalFilenames{ "Goal - Side.png","Goal - Back.png","Goal - Top.png" };
	loadFromFile(goalFilenames, m_goalTexture);

	std::vector<std::string> ScoreBoardfileNames{ "ScoreBoard.png"};
	loadFromFile(ScoreBoardfileNames, m_scoreBoardTexture);

	std::vector<std::string> gameMode{ "BackgroundGameMode.png", "Multiplayer.png" ,"Player.png", "Online.png"};
	loadFromFile(gameMode, m_gameModeTexture);

	std::vector<std::string> characters{ "ItalyPlayer.png" }; 
	loadFromFile(characters, m_characters);

	std::vector<std::string> balls{ "Ball 01.png","Ball 02.png"  };
	loadFromFile(balls, m_ballTexture);

	m_gameResultsTexture.push_back(m_gameModeTexture[0]);
	std::vector<std::string> gameResults{ "Replay.png"};
	loadFromFile(gameResults, m_gameResultsTexture);
	


	std::vector<std::string> gamePause{ "Pause.png","Resume.png", "Exit.png"};
	loadFromFile(gamePause, m_pauseTexture);

	std::vector<std::string> power{ "Progress Bar - Background.png","Progress Bar - Fill.png" };
	loadFromFile(power, m_powerTexture);

	if (!m_font.loadFromFile("Font.otf"))
	{
		throw FileException("Font file not load!");
	}

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

//getGoalTexture

std::vector<sf::Texture>& Resources::getPowerTexture()
{
	return m_powerTexture;
}

std::vector<sf::Texture>& Resources::getPauseTexture()
{
	return m_pauseTexture;
}

sf::Texture& Resources::getGoalTexture(int index) {

	return m_goalTexture[index];
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


//gameResultsTexture
std::vector<sf::Texture>& Resources::getBallTexture() {

	return m_ballTexture;
}

//getFont
sf::Font & Resources::getFont() {

	return m_font;
}

//get game mode selection
std::vector<sf::Texture>& Resources::getGameModeTexture() {
	return m_gameModeTexture;
}

//get characters
std::vector<sf::Texture>& Resources::getCharactersTexture() {

	return m_characters;
}
