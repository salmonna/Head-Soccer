

#pragma once
#include "Resources.h"
#include "FileException.h"
#include <iostream>

//constractor of resources file are loading files
Resources::Resources():m_selectedIndex(0){


	std::vector<std::string> fileNames{"Play.png","Quit.png","Setting.png", "Tutorial.png","Stage.png","Sounds.png","Music.png" ,"undo Button.png", "Tutorial State.png"};
	loadFromFile(fileNames,m_menuTexture);

	std::vector<std::string> boardFileNames{ "Stadium.png", "Ad Board.png","Goal.png"};
	loadFromFile(boardFileNames, m_boardTexture);

	std::vector<std::string> goalFilenames{ "Goal - Side.png","Goal - Back.png","Goal - Top.png" };
	loadFromFile(goalFilenames, m_goalTexture);

	std::vector<std::string> ScoreBoardfileNames{ "ScoreBoard.png"};
	loadFromFile(ScoreBoardfileNames, m_scoreBoardTexture);

	std::vector<std::string> gameMode{ "BackgroundGameMode.png", "Multiplayer.png" ,"Player.png", "Online.png","BackgroundGameMode2.png" };
	loadFromFile(gameMode, m_gameModeTexture);

	std::vector<std::string> characters{"BrazilianPlayer.png", "ItalyPlayer.png","EnglandPlayer.png",
										"SpainPlayer.png","HolandPlayer.png","PortugalPLayer.png","GermanyPlayer.png" }; 
	loadFromFile(characters, m_charactersSheet);

	std::vector<std::string> balls{ "Ball 01.png","Ball 02.png", "Ball 03.png", "Ball 04.png" };
	loadFromFile(balls, m_ballTexture);

	std::vector<std::string> selectTeam{ "brazilCharcter.png", "italyCharcter.png" ,"englandCharcter.png",
										"spainCharcter.png","holandCharcter.png","portugalCharcter.png","germanyCharcter.png","start.png","SelectTeam.png","frame.png" };
	loadFromFile(selectTeam, m_selectTeam);

	m_gameResultsTexture.push_back(m_gameModeTexture[0]);
	std::vector<std::string> gameResults{ "Replay.png","winner.png","draw.png"};
	loadFromFile(gameResults, m_gameResultsTexture);

	//std::vector<std::string> flags{"Brazil.png","Italy.png","England.png","Spain.png","Holand.png","Portugal.png","Germany.png"};
	//loadFromFile(flags, m_countryFlags);

	std::vector<std::string> gamePause{ "Pause.png","Resume.png", "Exit.png"};
	loadFromFile(gamePause, m_pauseTexture);

	std::vector<std::string> power{ "Progress Bar - Background.png","Progress Bar - Fill.png",  "Aura.png" ,"Tornado Power.png", "Kame Hame Ha.png",};
	loadFromFile(power, m_powerTexture);

	sf::Image im;
	im.loadFromFile("electricPower.png");
	im.createMaskFromColor(sf::Color(8, 0, 15));
	im.createMaskFromColor(sf::Color::Black);
	sf::Texture texture;
	texture.loadFromImage(im);
	m_powerTexture.push_back(texture);


	std::vector<std::string> powerOfPlayer{ "fireDragon.png"};
	loadFromFile(powerOfPlayer, m_powerOfPlayer);

	// Loading sound buffers.
	std::vector<std::string> soundStr = {"super saiyan sound.wav" };
	for (int i = 0; i < soundStr.size(); i++) {
		sf::SoundBuffer buffer;
		if (!buffer.loadFromFile(soundStr[i])) {
			throw FileException("sound file not load!");
		}
		m_bufferVec.push_back(buffer);
	}


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

std::vector<sf::Texture>& Resources::getPlayerPower() {

	return m_powerOfPlayer;
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
sf::Texture& Resources::getCharactersTexture() {

	if (m_selectedPlayer.size() < m_selectedIndex)
		m_selectedPlayer.push_back(0);

	int temp = m_selectedPlayer[m_selectedIndex];
	m_selectedIndex++;

	if (m_charactersSheet.size() < temp)
		throw FileException("No available character found");
	return m_charactersSheet[temp];
}
//get select team textures
std::vector<sf::Texture>& Resources::getSelectTeam() {

	return m_selectTeam;
}

//get power
std::vector<sf::Texture>& Resources::getPowerTexture() {

	return m_powerTexture;
}


std::vector<sf::SoundBuffer>& Resources::getBufferVec()
{
	return m_bufferVec;
}

void Resources::setSelectedPlayer(int index) {

	m_selectedPlayer.push_back(index);
}


std::vector<int> Resources::getPlayerOrder() {
	return m_selectedPlayer;
}

void Resources::resetPlayerOrder() {
	m_selectedPlayer.clear();
	m_selectedIndex = 0;
}

//std::vector<sf::Texture>& Resources::getCountriesFlags() {
//
//	return m_countryFlags;
//}