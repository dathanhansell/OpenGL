#include "Game.h"
#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>
#include <gl\glut.h>
#include <stdio.h>
#include <iostream>

using namespace std;

void Init();

Game::Game()
{
	Init();
}

Game::~Game()
{
	delete audio;
	delete input;
	delete time;
}

void Game::Init() {
	
	audio = new Audio();
	
	input = new Input();
	time = new Time();
	graphics = new Graphics();
	
	return;
}
