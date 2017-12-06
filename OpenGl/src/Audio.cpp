#include "stdafx.h"
#include "Audio.h"
#include <iostream>
void Init();

Audio::Audio()
{
	Init();
}


Audio::~Audio()
{
}
void Audio::Init() {
	std::cout << "Initializing SDL Audio..." << std::endl;
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		printf("Initialize Error: %s\n", SDL_GetError());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Initialize Error", "Couldn't initialize SDL Audio", NULL);
		return;
	}
	std::cout << "Setting Up Audio Channels..." << std::endl;
	if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 1, 4096))
	{
		fprintf(stderr, "SDL_Mixer Error: %s\n", Mix_GetError());
	}
}