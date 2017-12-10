#include "stdafx.h"
#include "Time.h"

//Uint32 startTime;
Time::Time()
{
	SetStartTicks();
}
Time::~Time()
{

}
void Time::SetStartTicks()
{
	//startTime = SDL_GetTicks();
}
void Time::setDeltaTime() {
	//deltaReturn =   SDL_GetTicks() - deltaTMP;
	//deltaTMP = SDL_GetTicks();
	//deltaTime =  deltaReturn/1000;
}
/*
Uint32 Time::GetTicks() {
	return SDL_GetTicks() - startTime;
}
*/

