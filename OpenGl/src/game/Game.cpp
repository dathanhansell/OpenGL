#include "Game.h"
#include <stdio.h>
#include <iostream>

using namespace std;

Game::Game()
{
	Init();
}

Game::~Game()
{

	delete graphics;

}

void Game::Init() {

	graphics = new Graphics();	
	
}
