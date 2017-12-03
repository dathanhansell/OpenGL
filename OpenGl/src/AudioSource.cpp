#include "stdafx.h"
#include "AudioSource.h"
#include <SDL_mixer.h>

void AudioSource::Play(AudioClip Clip, int volume) {
	Mix_VolumeChunk(Clip.chunk, volume);
	if (Mix_PlayChannel(0, Clip.chunk, 0) < 0)
	{
		fprintf(stderr, "SDL_mixer Error: %s\n", Mix_GetError());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "SDL_mixer Error: Couldn't load clip:", NULL);
	}
}

AudioSource::AudioSource()
{
}


AudioSource::~AudioSource()
{
}
