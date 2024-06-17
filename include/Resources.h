
//================================ include =========================//
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

class Resources
{
public:

	static Resources& getInstance() {
		static Resources instance;
		return instance;
	}
	
	std::vector<sf::Texture>& gameResultsTexture();
	std::vector<sf::Texture>& getMenuTexture();
	std::vector<sf::Texture>& getBoardTexture();

	std::vector<sf::Texture>& getScoreBoardTexture();

	sf::Texture& getGoalTexture(int index);
	std::vector<sf::Texture>& getBallTexture();
	std::vector<sf::Texture>& getCharactersTexture();
	std::vector<sf::Texture>& getGameModeTexture();
	std::vector<sf::Texture>& getPauseTexture();
	std::vector<sf::Texture>& getPowerTexture();


	sf::Font & getFont();

private:

	// Delete copy constructor and assignment operator
	Resources(const Resources&) = delete;
	Resources& operator=(const Resources&) = delete;
	void loadFromFile(std::vector<std::string> fileNames, std::vector<sf::Texture>& texture);
	Resources();
	
	std::vector<sf::Texture> m_menuTexture;
	std::vector<sf::Texture> m_gameModeTexture;
	std::vector<sf::Texture> m_boardTexture;
	std::vector<sf::Texture> m_gameResultsTexture;
	std::vector<sf::Texture> m_scoreBoardTexture;
	std::vector<sf::Texture> m_characters;
	std::vector<sf::Texture> m_goalTexture;
	std::vector<sf::Texture> m_ballTexture;
	std::vector<sf::Texture> m_pauseTexture;
	std::vector<sf::Texture> m_powerTexture;


	sf::Font m_font;

};