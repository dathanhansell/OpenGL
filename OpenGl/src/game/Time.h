#pragma once


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
	 //Uint32 GetTicks();
};

