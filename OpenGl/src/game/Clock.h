#pragma once

namespace MGLE {
	class Clock
	{
		float deltaReturn;
		float deltaTMP;
	public:
		Clock();
		~Clock();
		float deltaTime;
		void setDeltaTime();
		void SetStartTicks();
		//Uint32 GetTicks();
	};

}