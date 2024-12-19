#include "SoundControl.h"
#include "Resources.h"
#include <SFML/Audio.hpp>

//---------------------------------------------------------------------
SoundControl::SoundControl()
{
	m_introSong.setBuffer(Resources::getInstance().getBufferVec()[2]);
	m_introSong.setVolume(10);

	m_whistle.setBuffer(Resources::getInstance().getBufferVec()[1]);
	m_whistle.setVolume(5);

	m_crowd.setBuffer(Resources::getInstance().getBufferVec()[3]);
	m_crowd.setVolume(25);

	m_goalSound.setBuffer(Resources::getInstance().getBufferVec()[4]);
	m_goalSound.setVolume(5);

}
//---------------------------------------------------------------------
//get intro song sound
sf::Sound& SoundControl::getIntroSong() {

	return m_introSong;
}
//---------------------------------------------------------------------
//get whistle sound
sf::Sound& SoundControl::getWhistle() {

	return m_whistle;
}
//---------------------------------------------------------------------
//get crowd sound
sf::Sound& SoundControl::getCrowd() {

	return m_crowd;
}

//---------------------------------------------------------------------
//get goal sound
sf::Sound& SoundControl::getGoalSound() {

	return m_goalSound;
}