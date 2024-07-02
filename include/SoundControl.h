#pragma once
#include <SFML/Audio.hpp>

class SoundControl
{
public:

	static SoundControl& getInstance() {
		static SoundControl instance;
		return instance;
	}
	
	sf::Sound& getIntroSong();
	sf::Sound& getWhistle();
	sf::Sound& getCrowd();
	sf::Sound& getGoalSound();
	~SoundControl() = default;

private:
	SoundControl(const SoundControl&) = delete;
	SoundControl& operator=(const SoundControl&) = delete;
	SoundControl();


	sf::Sound m_introSong;
	sf::Sound m_whistle;
	sf::Sound m_crowd;
	sf::Sound m_goalSound;
};