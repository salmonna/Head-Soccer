#include "SoundControl.h"
#include "Resources.h"
#include <SFML/Audio.hpp>


SoundControl::SoundControl()
{
	m_introSong.setBuffer(Resources::getInstance().getBufferVec()[2]);
	m_introSong.setVolume(15);

	m_whistle.setBuffer(Resources::getInstance().getBufferVec()[1]);
	m_whistle.setVolume(5);
}

sf::Sound& SoundControl::getIntroSong() {

	return m_introSong;
}

sf::Sound& SoundControl::getWhistle() {

	return m_whistle;
}