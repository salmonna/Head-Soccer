#include "Command/Sound.h"
//--------------------------------------------------------------------------------------
// Constructor: Initializes the Sound object with the given sf::Sound object
Sound::Sound(sf::Sound & sound):m_sound(sound)
{
}
//--------------------------------------------------------------------------------------
// Execute the sound command: Play the sound if it is paused, pause it if it is playing
void Sound::execute(){

	if (m_sound.getStatus() == sf::SoundSource::Playing)
	{
		m_sound.pause();
		
		return;
	}
	m_sound.play();

}
//--------------------------------------------------------------------------------------
// Destructor
Sound::~Sound()
{
}