#pragma once
#include "SDL.h"
#include <SDL_mixer.h>

	class AudioClip
	{
	public:
		Mix_Chunk *chunk;
		const char *file;
		void Load();
		AudioClip();
		AudioClip(const char* File);
		~AudioClip();
	};


