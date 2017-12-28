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
	Shader* activeShader;
	Shader reg,err;
	cModel* activeModel;
	cModel suz;
	
	Game::~Game()
	{
		Log("Exiting\n");
		Log("--------------------------------------------------------\n");
		Log("Done with Graphics\n");
		delete graphics;
		Log("Done with Input\n");
		delete input;
		
		delete resources;
		Log("Done with Resources\n");
		//creates error cuz probably tries to delete a member called activeShader 
		//but the compiler is talking about the one on the cpp
		//delete activeShader;
		Log("Done with activeShader\n");
		//delete activeModel;
		Log("Done with activeModel\n");
		Log("--------------------------------------------------------\n");
		Log("Exit Success!\n");
	}
	float x = 7;
	float y = 4;
	float z = 7;
	void Game::Init() {

		graphics = new Graphics();
		glClearColor(.85, .85, .85, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		graphics->window->Display();
		input = new Input();
		resources = new Resources();
		Shader::Init();
		cModel::Init();
		reg.CreateFromFile("reg", "shaders\\solid_v.glsl", "shaders\\solid_f.glsl");
		
		reg.AddUniform("MVP");
		reg.AddUniform("bobs");
		err.CreateFromFile("error","shaders\\error_v.glsl", "shaders\\error_f.glsl");
		err.AddUniform("MVP");
		activeShader = &reg;
		suz.LoadFromFile("erdror.obj");
		activeModel = &suz;

	}
	float c;
	int size = 5;
	bool is;
	void Game::Update() {
		if (GetActiveWindow() == 00000000) return;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		if (input->GetKey(input->W))       z -= .02f;
		if (input->GetKey(input->S))       z += .02f;
		if (input->GetKey(input->Space))   y += .02f;
		if (input->GetKey(input->LControl))y -= .02f;
		if (input->GetKey(input->D))       x += .02f;
		if (input->GetKey(input->A))       x -= .02f;
		if (input->GetKeyDown(input->E)) size++;
		if (input->GetKeyDown(input->Q)) size--;
		
		c += 1;
		m.Identity();
		p.Perspective(45, (float)graphics->window->GetWidth() / (float)graphics->window->GetHeight(), 0.1f, 200);
		v.View({x,y,z}, { 0, 0, 0 }, { 0, 1, 0 });
		m.Translate(0, 0, 0);
		MVP = m*v*p;
		activeShader = &err;
		activeShader->Bind();
		activeShader->SetUniform("MVP", MVP);
		activeModel->Draw();

		m.Identity();
		MVP = m*v*p;
		activeShader = &reg;
		activeShader->Bind();
		activeShader->SetUniform("MVP", MVP);
		activeShader->SetUniform("bobs", { .4f,.4f,.4f });
		
		Debug::DrawGrid(size);
		
		input->Update();
		graphics->window->Display();

	}
}