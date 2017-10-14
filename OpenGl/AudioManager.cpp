#include "stdafx.h"
#include "AudioManager.h"

void AudioManager::SetupAudio() {
	std::cout << "Setting Up Audio Channels..." << std::endl;
	if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 1, 4096))
	{
		fprintf(stderr, "SDL_Mixer Error: %s\n", Mix_GetError());
	}
}

AudioManager::AudioManager()
{
}


AudioManager::~AudioManager()
{
}
