#include "Timer.h"

Timer::Timer() {

}
Timer::~Timer() {

}

void Timer::Start() {
	m_isRunning = true;
	startTime = std::chrono::system_clock::now();
}
void Timer::Stop() {
	m_isRunning = false;
	endTime = std::chrono::system_clock::now();
}
double Timer::ElapsedMilliseconds() {
	std::chrono::time_point<std::chrono::system_clock> now;

	if (m_isRunning)
	{
		now = std::chrono::system_clock::now();
	}
	else
	{
		now = endTime;
	}

	return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
}
bool Timer::IsRunning()
{
	return m_isRunning;
}