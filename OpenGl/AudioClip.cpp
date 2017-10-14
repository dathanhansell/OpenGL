#include "stdafx.h"
#include"AudioClip.h"
#include <stdio.h>
#include <string>
#include <iostream>

void AudioClip::Load() {
	SDL_RWops *src = SDL_RWFromFile( file, "r");
	char *tmp = new char[strlen(file) + strlen("couldn't be loaded") + 1];
	strcpy(tmp, file);
	strcat(tmp, "couldn't be loaded");
	if (src == NULL) {
		printf("SDL_RWFromFile: %s\n", Mix_GetError());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_RWFromFile Error", tmp, NULL);
		exit(9);
	}
	chunk = Mix_LoadWAV_RW(src, 1);
	if (chunk == NULL) {
		printf("Mix_LoadWAV_RW: %s\n", Mix_GetError());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Mix_LoadWAV_RW Error", "Clip couldn't be loaded", NULL);
		exit(10);
	}
	delete tmp;
}
AudioClip::AudioClip() {

}
AudioClip::AudioClip(const char *File) {
	file = new char[strlen((const char*)SDL_GetBasePath()) + strlen(File) + 1];
	strcpy((char*)file, (const char*)SDL_GetBasePath());
	strcat((char*)file, File);
}
AudioClip::~AudioClip() {

}
