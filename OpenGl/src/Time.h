#pragma once
#include <SDL.h>

class Time
{
	 float deltaReturn;
	 float deltaTMP;
public:
	Time();
	~Time();
	 float deltaTime;
	 void setDeltaTime();
	 void SetStartTicks();
	 Uint32 GetTicks();
};

