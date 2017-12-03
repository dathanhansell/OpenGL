#pragma once
#include <SDL.h>

class Time
{
	static float deltaReturn;
	static float deltaTMP;
public:
	static float deltaTime;
	static void setDeltaTime();
	static void SetStartTicks();
	static Uint32 GetTicks();
};

