#pragma once
#include <MGLE.h>
class Graphics;
class Game {
public:
	Graphics* graphics;
	Game();
	~Game();
	void Init();
};

