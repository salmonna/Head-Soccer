#pragma once
#include "Command.h"
#include <SFML/Audio.hpp>

class Sound :public Command
{
public:
	Sound(sf::Sound & sound);

	virtual void execute()override;

	virtual ~Sound();

private:

	sf::Sound& m_sound;
};