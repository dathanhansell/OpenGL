#pragma once
#include "stdafx.h"
#include <MGLE.h>
class Graphics;
class Resources;
class Input;
class Timer;
class Game {
public:
	Input* input;
	Graphics* graphics;
	Resources* resources;
	Game();
	~Game();
	void Init();
	void Update();
	void drawText(std::string text, int x, int y);
};

