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
	delete resources;
	delete input;
	delete graphics;
}
Model model;
void Game::Init() {
	input = new Input();
	resources = new Resources();
	graphics = new Graphics();	
	model = resources->objloader->loadOBJ("C:/test.obj");
	glClearColor(.3f, .3f, .3f, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, graphics->window->GetWidth(), graphics->window->GetHeight());
	glOrtho(-10, 10, 10, -10, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
	//gluLookAt(1, 4, 0, .8f, 0, 0, 0, 1, 0);
}
int x=0;
int y=0;
void Game::drawText(string text, int x, int y) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, graphics->window->GetWidth(), 0, graphics->window->GetHeight(), -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glRasterPos2i(x, y);
	for (int i = 0; i < text.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)text[i]);
	glPopMatrix();
}
void Game::Update() {
	input->Update();
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	glPushMatrix();

	
	if (input->GetKey(input->W))y += 1;

	if (input->GetKey(input->S))y -= 1;

	if (input->GetKey(input->A))x -= 1;

	if (input->GetKey(input->D))x += 1;
	std::stringstream ss;
	ss << "Test: x:" << x << " y:" << y;
	drawText(ss.str(), x, y);
	glPopMatrix();
	graphics->window->Display();
	

}
