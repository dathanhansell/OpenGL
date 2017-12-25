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
	cModel* mod;
	cModel ico,suz;
	Game::~Game()
	{
		Log("Exiting\n");
		Log("--------------------------------------------------------\n");
		Log("Done with Graphics\n");
		delete graphics;
		Log("Done with Input\n");
		delete input;
		Log("Done with Resources\n");
		delete resources;
		delete shad;
		Log("--------------------------------------------------------\n");
		Log("Exit Success!\n");
	}
	float x = 0;
	float y = 1;
	float z = 3;
	void Game::Init() {

		graphics = new Graphics();
		input = new Input();
		resources = new Resources();
		shad = new Shader("shaders\\vert.glsl", "shaders\\frag.glsl");
		ico.LoadFromFile("ico.obj");
		suz.LoadFromFile("suz.obj");
		mod = &suz;

	}
	float c;
	Vector3 color = { 0,1,1 };
	bool is;
	void Game::Update() {
		glClearColor(.85, .85, .85, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (input->GetKey(input->W))       z -= .02f;
		if (input->GetKey(input->S))       z += .02f;
		if (input->GetKey(input->Space))   y += .02f;
		if (input->GetKey(input->LControl))y -= .02f;
		if (input->GetKey(input->D))       x += .02f;
		if (input->GetKey(input->A))       x -= .02f;
		if (input->GetKeyDown(input->E)) {
			is = !is;
			if (is)
				mod = &ico;
			else
				mod = &suz;
		}

		c += 1;
		color = { (sinf(c*.04)*.5f) + 1,(cosf(c*.02)*.5f)+1,(sinf(c*.01)*.5f) + 1 };
		m.Identity();
		p.Perspective(45, (float)graphics->window->GetWidth() / (float)graphics->window->GetHeight(), 0.1f, 100.0f);
		v.View({x,y,z}, { 0, 0, 0 }, { 0, 1, 0 });
		m.Translate({0,sinf(c*.01)*.5f,0});
		m.rotate(c,0,1,0);
		MVP = m*v*p;
		shad->SetUniform("MVP", MVP);
		shad->SetUniform("M", m);
		shad->SetUniform("V", v);
		shad->SetUniform("base_color", color);
		shad->Bind();
		mod->Draw();
		input->Update();

	}
}