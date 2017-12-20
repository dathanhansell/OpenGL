#include "stdafx.h"
#include "Clock.h"
namespace MGLE {
	//Uint32 startTime;
	Clock::Clock()
	{
		SetStartTicks();
	}
	Clock::~Clock()
	{

	}
	void Clock::SetStartTicks()
	{
		//startTime = SDL_GetTicks();
	}
	void Clock::setDeltaTime() {
		//deltaReturn =   SDL_GetTicks() - deltaTMP;
		//deltaTMP = SDL_GetTicks();
		//deltaTime =  deltaReturn/1000;
	}
	/*
	Uint32 Time::GetTicks() {
		return SDL_GetTicks() - startTime;
	}
	*/
}
