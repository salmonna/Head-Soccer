#include "Command/Sound.h"

Sound::Sound(sf::Sound & sound):m_sound(sound)
{
}

void Sound::execute(){

	if (m_sound.getStatus() == sf::SoundSource::Playing)
	{
		m_sound.pause();
		
		return;
	}
	m_sound.play();

}

Sound::~Sound()
{
}