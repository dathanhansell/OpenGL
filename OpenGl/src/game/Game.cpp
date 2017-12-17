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
	glClearColor(.05f, .05f, .05f, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, graphics->window->GetWidth(), graphics->window->GetHeight());
	gluPerspective(90, graphics->window->GetWidth()/ graphics->window->GetHeight(),.1,50);
	glMatrixMode(GL_MODELVIEW);
	//gluLookAt(1, 4, 0, .8f, 0, 0, 0, 1, 0);
}
int x=0;
int y=0;
int w = 0;
int h = 0;
void Game::drawText(string text, int x, int y) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, 0, h, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glRasterPos2i(x, y);
	for (int i = 0; i < text.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)text[i]);
	glPopMatrix();
}


void Game::Update() {
	
	input->Update();
	w = graphics->window->GetWidth();
	h = graphics->window->GetHeight();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glColor3f(1,1,1);
	if (input->GetKey(input->W))y += 2;
	if (input->GetKey(input->S))y -= 2;
	if (input->GetKey(input->A))x -= 2;
	if (input->GetKey(input->D))x += 2;
	std::stringstream ss;
	ss << "Test: x:" << x << " y:" << y;
	drawText(ss.str(), x, y);
	glPopMatrix();

	
	

}
