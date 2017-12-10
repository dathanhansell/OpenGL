#pragma once
#include <stdafx.h>
#include <MGLE.h>
class Window {
	int height;
	int width;

	bool fullscreen;
	void Init();
	void ResetWindow();
public:
	Window();
	~Window();
	int GetWidth();
	int GetHeight();

};