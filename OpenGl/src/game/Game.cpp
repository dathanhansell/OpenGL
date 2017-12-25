#include "Game.h"
#include <stdio.h>
#include <iostream>
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
	float y = 2;
	float z = 3;
	void Game::Init() {

		graphics = new Graphics();
		input = new Input();
		resources = new Resources();
		shad = new Shader("shaders\\vert.glsl", "shaders\\frag.glsl");
		mod.LoadFromFile("test.obj");

		mod.Draw();
	}
	float c;
	void Game::Update() {
		glClearColor(.3, .3, .3, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		c += .008;
		m.Identity();
		p.Perspective(45, (float)graphics->window->GetWidth() / (float)graphics->window->GetHeight(), 0.1f, 100.0f);
		v.View({sinf(c) *z, y, cosf(c)*z },{ 0, 0, 0 },{ 0, 1, 0 });
		m.Translate({0,0,0});
		MVP = m*v*p;

		
		if (input->GetKey(input->W))       z -= .02f;
		if (input->GetKey(input->S))       z += .02f;
		if (input->GetKey(input->Space))   y += .02f;
		if (input->GetKey(input->LControl))y -= .02f;
		if (input->GetKey(input->D))       x += .02f;
		if (input->GetKey(input->A))       x -= .02f;

		shad->SetUniform("MVP", MVP);

		shad->Bind();
		mod.Draw();
		/*
		m.Translate({ 1,0,1 });
		M = glm::translate(glm::mat4(1.0f), glm::vec3(1,0,1));
		MVP = m*v*p;
		mvp = M*V*P;
		if (glm)
			shad->SetUniform("MVP", mvp);
		else
			shad->SetUniform("MVP", MVP);

		mod.Draw();
		*/

		input->Update();
	}
}