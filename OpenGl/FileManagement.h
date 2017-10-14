#pragma once
#include "SDL.h"
class FileManagement
{
public:
	FileManagement();
	~FileManagement();
	static FileManagement FM;
	const char* ExecutibleDirectory = &SDL_GetBasePath;
};

