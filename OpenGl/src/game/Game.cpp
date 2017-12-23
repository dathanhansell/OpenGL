#include "Game.h"
#include <stdio.h>
#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include"gtx/string_cast.hpp"
using namespace std;
namespace MGLE {
	Game::Game()
	{
		Init();

	}
	Mat4x4 m, v, p, MVP;
	glm::mat4 mProjection, mModel, mView,mvp;

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
	float x = 3;
	float z = 3;
	void Game::Init() {

		graphics = new Graphics();
		input = new Input();
		resources = new Resources();

		p = p.Perspective(90.0f, 1.0f, 0.1f, 100.0f);
		mProjection = glm::perspective(90.0f, 1.0f, 0.1f, 100.0f);
		
		
		m = m.Identity();
		mModel = glm::mat4(1.0f);
		
		
		shad = new Shader("shaders\\vert.glsl", "shaders\\frag.glsl");
		mod = resources->objloader->LoadOBJ("test.obj");
	}
	float c;
	bool mg;
	void Game::Update() {
		glClearColor(.2f, .2f, .2f, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		c += .0016;
		glPushMatrix();

		v = v.View({ (float)sin(c*(2 * M_PI))*3, 1, (float)cos(c*(2 * M_PI))*3 },
		{ 0, 0, 0 },
		{ 0, 1, 0 });
		mView = glm::lookAt(
			glm::vec3((float)sin(c*(2 * M_PI)) * 3, 1, (float)cos(c*(2 * M_PI)) * 3),
			glm::vec3(0, 0, 0),
			glm::vec3(0, 1, 0)
		);
		mvp = mProjection * mView * mModel;
		MVP = m*v*p;
		if (input->GetKeyDown(input->E)) {
			Log("M: %s\n", glm::to_string(mModel).c_str());
			Log("V: %s\n", glm::to_string(mView).c_str());
			Log("P: %s\n", glm::to_string(mProjection).c_str());
			Log("MVP: %s\n", glm::to_string(mvp).c_str());
			Log("\n M: %s\n", m.toString().c_str());
			Vector3 view = { -3,-1,-3 };
			Log(" Viewf: %f,%f,%f\n", view.normalized().x, view.normalized().y, view.normalized().z);
			Log(" V: %s\n", v.toString().c_str());
			Log(" P: %s\n", p.toString().c_str());
			Log(" MVP: %s\n", MVP.toString().c_str());

		}
		// Our ModelViewProjection : multiplication of our 3 matrices
		
		if (input->GetKey(input->W))z += .2f;
		if (input->GetKey(input->S))z -= .2f;
		if (input->GetKey(input->D))x += .2f;
		if (input->GetKey(input->A))x -= .2f;
		if (input->GetKeyDown(input->Space))mg = !mg;
		
		if(mg)shad->SetUniform("MVP", MVP);
		else shad->SetUniform("MVP", mvp);

		shad->Bind();
		mod.Draw();

		input->Update();
	}
}