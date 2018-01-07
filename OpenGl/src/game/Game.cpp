#include "Game.h"
#include "GameObject.h"
#include "Cubemap.h"
#include <stdio.h>
#include <iostream>
#include <math.h>

using namespace std;
namespace MGLE {
	Game::Game()
	{
		Init();
	}
	Mat4x4 m, v, p, MVP;
	Shader* activeShader;
	Shader reg, ref, bas;
	cModel* activeModel;
	cModel testModel, sBox;
	cCubemap cubemap;

	Game::~Game()
	{
		
		Log("Exiting\n");
		OpenBar();
		delete graphics;
		Log("Done with Graphics\n");
		delete input;
		Log("Done with Input\n");
		delete resources;
		Log("Done with Resources\n");
		CloseBar();
		Log("Exit Success!\n");
	}
	Vector3 pos, tar;
	
	void Game::Init() {
		
		graphics = new Graphics();
		
		glClearColor(.85, .85, .85, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		graphics->window->Display();
		input = new Input();
		
		resources = new Resources();
		
		Shader::Init();
		cModel::Init();

		reg.CreateProgram("reg", "shaders\\solid_v.glsl", "shaders\\solid_f.glsl");
		reg.AddUniform("MVP");
		reg.AddUniform("bobs");

		ref.CreateProgram("reflective", "shaders\\reflective_v.glsl", "shaders\\reflective_f.glsl");
		ref.AddUniform("M");
		ref.AddUniform("V");
		ref.AddUniform("P");
		ref.AddUniform("cPos");
		ref.AddUniform("cubemap");

		bas.CreateProgram("bas", "shaders\\skybox_v.glsl", "shaders\\skybox_f.glsl");
		bas.AddUniform("VP");

		bas.AddUniform("cubemap");
		activeShader = &reg;
		sBox.CreateModel("skybox", "uvCube.obj");
		testModel.CreateModel("testModel", "suz.obj");
		activeModel = &testModel;
		pos = { 0,0,4 };
		cubemap.LoadFromFile("posx.jpg", "negx.jpg", "posy.jpg", "negy.jpg","posz.jpg", "negz.jpg");
		//cubemap.LoadFromFile("posx1.jpg", "posx1.jpg", "posy1.jpg", "posy1.jpg", "posx1.jpg", "posx1.jpg");
		//cubemap.LoadFromFile("null.png", "null.png", "null.png", "null.png", "null.png", "null.png");

	}
	float x, y, zm = 5;
	int size = 5;
	bool wf;
	Vector3 scale = { 1,1,1 };
	void Game::Update() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		sf::Event e;
		while (graphics->window->GetWindow()->pollEvent(e)) {
			if (e.type == sf::Event::Closed)
				graphics->window->GetWindow()->close();
			if (e.type == sf::Event::Resized)
			{
				graphics->window->Reshape(e.size.width, e.size.height);
			}
			if (e.type == sf::Event::MouseWheelMoved)
			{
				zm += -e.mouseWheel.delta*.5;
				if (zm <= 0) zm = .5;
			}
		}
		if (GetActiveWindow() == 00000000) return;
		if (input->GetKeyDown(input->W))      zm--;
		if (input->GetKeyDown(input->S))      zm++;
		if (input->GetKey(input->Space));
		if (input->GetKey(input->LControl));
		if (input->GetKey(input->D));
		if (input->GetKey(input->A));
		if (input->GetKeyDown(input->E)) size++;
		if (input->GetKeyDown(input->Q)) size--;
		if (input->GetKeyDown(input->F)) wf = !wf;
		if (wf) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glEnable(GL_CULL_FACE);
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glDisable(GL_CULL_FACE);
		}
		pos = { 0,0,0 };
		pos += { -sin(x)* cos(y),
			sin(y),
			cos(x) * cos(y)};
		pos *= zm;
		if (input->GetMouseButton(input->Middle)) {
			if (!input->GetKey(input->LShift)) {
				x += input->GetMouse().x;
				y -= input->GetMouse().y;
				if (y >= 1.57) y = 1.569f;
				if (y <= -1.57) y = -1.569f;
			}
			else {
				Vector3 f = pos.normalized();
				Vector3 r = Vector3::Cross(f, { 0,1,0 });
				f.y = 0;
				r.Normalize();
				f.Normalize();
				f *= input->GetMouse().y;
				r *= input->GetMouse().x;
				f += r;
				tar += f;
			}
		}

		pos += tar;

		m.Identity();
		p.Perspective(90, (float)graphics->window->GetWidth() / (float)graphics->window->GetHeight(), 0.1f, 200);
		//p.Orthographic(-.05,.05,-.05,.05,.1,100);
		v.View({ pos.x,pos.y,pos.z }, { tar.x, tar.y, tar.z }, { 0, 1, 0 });

		glDisable(GL_DEPTH_TEST);
		
		input->Update();
		m.Identity();
		m.Translate(pos);
		MVP = m*v * p;
		activeModel = &sBox;
		activeShader = &bas;
		activeShader->Bind();
		activeShader->SetUniform("VP", MVP);


		cubemap.Bind();
		activeShader->SetUniform("cubemap", 0);
		activeModel->Draw();
		glEnable(GL_DEPTH_TEST);


		m.Identity();
		MVP = m*v*p;
		activeModel = &testModel;
		activeShader = &ref;
		activeShader->Bind();
		activeShader->SetUniform("M", m);
		activeShader->SetUniform("V", v);
		activeShader->SetUniform("P", p);
		activeShader->SetUniform("cPos", pos);
		cubemap.Bind();
		activeShader->SetUniform("cubemap", 0);
		activeModel->Draw();

		

		m.Identity();
		MVP = m*v*p;
		activeShader = &reg;
		activeShader->Bind();
		activeShader->SetUniform("MVP", MVP);
		activeShader->SetUniform("bobs", { .4f,.4f,.4f });

		Debug::DrawGrid(size);
		m.Translate(tar);
		m.Scale(.1f, .1f, .1f);
		MVP = m*v*p;
		
		activeShader->SetUniform("MVP", MVP);
		activeShader->SetUniform("bobs", { 1,0,1 });
		Debug::DrawWireSphere({ 0,0,0 });
		
		graphics->window->Display();
	}
}