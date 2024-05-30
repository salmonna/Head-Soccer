
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
	sf::Font & getFont();

private:

	// Delete copy constructor and assignment operator
	Resources(const Resources&) = delete;
	Resources& operator=(const Resources&) = delete;
	void loadFromFile(std::vector<std::string> fileNames, std::vector<sf::Texture>& texture);
	Resources();
	
	std::vector<sf::Texture> m_menuTexture;
	std::vector<sf::Texture> m_boardTexture;
	std::vector<sf::Texture> m_gameResultsTexture;
	sf::Font m_font;

};