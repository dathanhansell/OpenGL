#pragma once
class Graphics
{
	int height;
	int width;
	bool fullscreen;
	bool InitGL();
	bool InitGLEW();
	void ResetWindow();
public:
	
	Graphics();
	~Graphics();
	void Init();
};

