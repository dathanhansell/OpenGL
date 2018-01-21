#include "Game.h"
#include "Cubemap.h"
#include "cmath"                   // for cos, sin
#include "GL/glew.h"               // for glClear, glDisable, glEnable, glPolygonMode, glClearColor, GL_COLOR_BUFFER_BIT, GL_CULL_FACE, GL_DEPTH_BUFFER_BIT, GL_DEPTH_TEST, GL_FRONT_AND_BACK, GL_FILL, GL_LINE
#include "Graphics.h"              // for Graphics
#include "Input.h"                 // for Input
#include "LowLevelSystem.h"        // for Log, CloseBar, OpenBar
#include "Mat4x4.h"                // for Mat4x4
#include "Model.h"                 // for cModel
#include "Resources.h"             // for Resources
#include "SFML/Window/Event.hpp"   // for Event, Event::(anonymous), Event::SizeEvent, Event::EventType::Closed, Event::EventType::MouseWheelMoved, Event::EventType::Resized, Event::MouseWheelEvent
#include "SFML/Window/Window.hpp"  // for Window
#include "Shader.h"                // for Shader
#include "vcruntime_new.h"         // for operator delete, operator new
#include "Vector2.h"               // for Vector2
#include "Vector3.h"               // for Vector3
#include "Window.h"                // for Window
#include "WinUser.h"               // for GetActiveWindow

using namespace std;
	Game::Game()
	{
		Init();
	}
	Mat4x4 m, v, p, MVP;
	Shader* activeShader;
	Shader reg, refl, bas;
	cModel* activeModel;
	cModel testModel, sBox;
	cCubemap* activeCube;
	cCubemap c1, c2, c3;

	Game::~Game()
	{

		Log("Exiting\n");
		OpenBar();
		//delete graphics;
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
		
		//graphics = new Graphics();

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

		refl.CreateProgram("reflective", "shaders\\reflective_v.glsl", "shaders\\reflective_f.glsl");
		refl.AddUniform("M");
		refl.AddUniform("V");
		refl.AddUniform("P");
		refl.AddUniform("cPos");
		refl.AddUniform("cubemap");

		bas.CreateProgram("bas", "shaders\\skybox_v.glsl", "shaders\\skybox_f.glsl");
		bas.AddUniform("VP");

		bas.AddUniform("cubemap");
		activeShader = &reg;
		sBox.CreateModel("skybox", "uvCube.obj");
		testModel.CreateModel("testModel", "suz.obj");
		activeModel = &testModel;
		pos = { 0,0,4 };
		c1.LoadFromFile("posx.jpg", "negx.jpg", "posy.jpg", "negy.jpg", "posz.jpg", "negz.jpg");
		activeCube = &c1;
		activeCube->Bind();
		c3.LoadFromFile("posx2.jpg", "negx2.jpg", "posy2.jpg", "negy2.jpg", "posz2.jpg", "negz2.jpg");
		c2.LoadFromFile("posx3.jpg", "negx3.jpg", "posy3.jpg", "negy3.jpg", "posz3.jpg", "negz3.jpg");
		//cubemap.LoadFromFile("posx1.jpg", "posx1.jpg", "posy1.jpg", "posy1.jpg", "posx1.jpg", "posx1.jpg");
		//cubemap.LoadFromFile("null.png", "null.png", "null.png", "null.png", "null.png", "null.png");

	}
	float x, y, zm = 5;
	int isize = 5, kyoob = 0;
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
		if (input->GetKeyDown(input->E)) isize++;
		if (input->GetKeyDown(input->Q)) isize--;
		if (input->GetKeyDown(input->F)) wf = !wf;
		if (input->GetKeyDown(input->C)) {
			switch (kyoob)
			{
			case 0:
				activeCube = &c1;
				break;
			case 1:
				activeCube = &c2;
				break;
			case 2:
				activeCube = &c3;
				kyoob =-1;
				break;
			default:
				break;
			}
			kyoob++;
			activeCube->Bind();
		}
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
		activeShader->SetUniform("cubemap", 0);
		activeModel->Draw();
		glEnable(GL_DEPTH_TEST);


		m.Identity();
		MVP = m*v*p;
		activeModel = &testModel;
		activeShader = &refl;
		activeShader->Bind();
		activeShader->SetUniform("M", m);
		activeShader->SetUniform("V", v);
		activeShader->SetUniform("P", p);
		activeShader->SetUniform("cPos", pos);
		activeShader->SetUniform("cubemap", 0);
		activeModel->Draw();


/*
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
		*/
		graphics->window->Display();
	}
