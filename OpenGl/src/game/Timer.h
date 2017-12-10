#pragma once
#include <stdafx.h>
class Timer {
	std::chrono::time_point<std::chrono::system_clock> startTime;
	std::chrono::time_point<std::chrono::system_clock> endTime;
	bool m_isRunning;
public:
	bool IsRunning();
	void Start();
	void Stop();
	double ElapsedMilliseconds();
	Timer();
	~Timer();
};