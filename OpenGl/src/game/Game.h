#pragma once
#include "tString.h"  // for string

	class Graphics;
	class Resources;
	class Input;
	class Game {
	public:
		Input* input;
		Graphics* graphics;
		Resources* resources;
		Game();
		~Game();
		void Init();
		void Update();
		void drawText(tString text, int x, int y);
	};

