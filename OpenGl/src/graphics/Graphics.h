#pragma once
#include <stdafx.h>
#include <MGLE.h>


class Timer;
class Window;
class Graphics
{
	static void RenderCallBack();
	Timer frameTimer;
	int frameCount;
	bool InitGL();
	bool InitGLEW();
	void Render();
	void Init();
public:
	Window* window;
	Graphics();
	~Graphics();

};

