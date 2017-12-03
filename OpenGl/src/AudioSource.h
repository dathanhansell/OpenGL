#pragma once
#include "AudioClip.h"
class AudioSource
{
public:
	void Play(AudioClip Clip,int volume = 128);
	AudioSource();
	~AudioSource();
};

