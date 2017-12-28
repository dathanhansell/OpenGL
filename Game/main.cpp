// Game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <MGLE.h>
#include <SFML/System.hpp>


using namespace MGLE;
Game* mGame;
	int main(int argc, char** argv)
	{
		glutInit(&argc, argv);
		mGame = new Game();

		while (mGame->graphics->window->Open()) {
			sf::sleep(sf::microseconds(16667));
			mGame->Update();
			
			mGame->graphics->window->PollEvents();
		}
		delete mGame;
		return 0;
	}



