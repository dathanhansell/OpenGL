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
}

void Game::Init() {
	audio = new Audio();
	game = new Game();
	input = new Input();
	time = new Time();
	glutMainLoop();
	return;
}
