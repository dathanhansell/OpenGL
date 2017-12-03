#pragma once
#include "Audio.h"
#include "Input.h"
#include "Time.h"
class Game
{
public:
	Audio* audio;
	Game* game;
	Input* input;
	Time* time;
	Game();
	~Game();
	void Init();
};

