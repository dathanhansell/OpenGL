#include "Game.h"
#include <stdio.h>
#include <iostream>
#include <glm.hpp>
#include <vec3.hpp>
#include <gtc/matrix_transform.hpp>
#include"gtx/string_cast.hpp"
using namespace std;
namespace MGLE {
	Game::Game()
	{
		Init();

	}
	Mat4x4 m, v, p, MVP;

	Shader* shad;
	cModel mod;
	Game::~Game()
	{
		Log("Exiting System Module\n");
		Log("--------------------------------------------------------\n");
		Log("Done with Graphics\n");
		delete graphics;
		Log("Done with Input\n");
		delete input;
		Log("Done with Resources\n");
		delete resources;
		delete shad;
		Log("--------------------------------------------------------\n\n");
	}
	float x = 0;
	float y = 0;
	float z = 0;
	void Game::Init() {

		graphics = new Graphics();
		input = new Input();
		resources = new Resources();
		shad = new Shader("shaders\\vert.glsl", "shaders\\frag.glsl");
		mod = resources->objloader->LoadOBJ("test.obj");
	}
	float c;
	void Game::Update() {
		glClearColor(.3, .3, .68, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		c += .001;
		
		m = m.Identity();
		p = p.Perspective(90.0f, (float)graphics->window->GetWidth() / (float)graphics->window->GetHeight(), 0.1f, 100.0f);
		v = v.View({(float)sin(c*(2 * M_PI))*6, 1, (float)cos(c*(2 * M_PI))*6 },{ 0, 0, 0 },{ 0, 1, 0 });
		m.Translate({x,y,z});
		MVP = m*v*p;
		
		if (input->GetKey(input->W))z += .2f;
		if (input->GetKey(input->S))z -= .2f;
		if (input->GetKey(input->Space))y += .2f;
		if (input->GetKey(input->LControl))y -= .2f;
		if (input->GetKey(input->D))x += .2f;
		if (input->GetKey(input->A))x -= .2f;

		shad->SetUniform("MVP", MVP);

		shad->Bind();
		mod.Draw();

		input->Update();
	}
}