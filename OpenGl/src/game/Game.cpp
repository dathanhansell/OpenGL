#include "Game.h"
#include <stdio.h>
#include <iostream>

using namespace std;
namespace MGLE {
	Game::Game()
	{
		Init();
		
	}

	Game::~Game()
	{
		delete resources;
		delete input;
		delete graphics;
	}
	Model model;
	void Game::Init() {
		graphics = new Graphics();
		input = new Input();
		resources = new Resources();
		
		model = resources->objloader->loadOBJ("test.obj");
		glClearColor(.05f, .05f, .05f, 1);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glViewport(0, 0, graphics->window->GetWidth(), graphics->window->GetHeight());
		gluPerspective(90, graphics->window->GetWidth() / graphics->window->GetHeight(), .1, 50);
		glMatrixMode(GL_MODELVIEW);
		//gluLookAt(1, 4, 0, .8f, 0, 0, 0, 1, 0);
	}
	void Game::Update() {
		input->Update();
	}
}