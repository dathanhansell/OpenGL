#pragma once
#include "Audio.h"
#include "Graphics.h"
#include "Input.h"
#include "Time.h"
class Game
{
public:
	Audio* audio;
	Input* input;
	Time* time;
	Graphics* graphics;
	Game();
	~Game();
	void Init();
};

