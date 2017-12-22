#include "Game.h"
#include <stdio.h>
#include <iostream>

using namespace std;
namespace MGLE {
	Game::Game()
	{
		Init();
		
	}
	Mat4x4 mat;
	Shader* shad;
	//Model* mod;
	Game::~Game()
	{
		delete resources;
		delete input;
		delete graphics;
		delete shad;
	}
	
	void Game::Init() {

		graphics = new Graphics();
		input = new Input();
		resources = new Resources();
		
		mat.Perspective(90, 16 / 9, 0.001f, 1000);
		shad = new Shader("shaders\\vert.glsl", "shaders\\frag.glsl");
		shad->AddUniform("MVP");
		//mod = &resources->objloader->loadOBJ("test.obj");
	}
	void Game::Update() {
		input->Update();
		//shad->SetUniform("MVP",mat);
		//glUseProgram(shad->GetProgramID());
		//mod->Draw();
	}
}