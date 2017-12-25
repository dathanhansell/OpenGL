#pragma once
#include <stdafx.h>
#include <MGLE.h>

namespace MGLE {
	class Timer;
	class Window;
	class Renderer;
	class Graphics
	{
		
		Renderer* renderer;
		Timer frameTimer;
		int frameCount;
		bool InitGL();
		bool InitGLEW();
		void Render();
		
		void Init();
	public:
		void FPS();
		Window* window;
		Graphics();
		~Graphics();

	};
}
