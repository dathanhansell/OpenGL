#include "Game.h"
#include "GL/glew.h"               // for glClear, glDisable, glEnable, glPolygonMode, glClearColor, GL_COLOR_BUFFER_BIT, GL_CULL_FACE, GL_DEPTH_BUFFER_BIT, GL_DEPTH_TEST, GL_FRONT_AND_BACK, GL_FILL, GL_LINE
#include "Graphics.h"              // for Graphics
#include "Input.h"                 // for Input
#include "LowLevelSystem.h"        // for Log, CloseBar, OpenBar
#include "Mat4x4.h"                // for Mat4x4
#include "Model.h"                 // for cModel
#include "Resources.h"             // for Resources
#include "SFML/Window/Event.hpp"   // for Event, Event::(anonymous), Event::SizeEvent, Event::EventType::Closed, Event::EventType::MouseWheelMoved, Event::EventType::Resized, Event::MouseWheelEvent
#include "Shader.h"                // for Shader
#include "vcruntime_new.h"         // for operator delete, operator new
#include "Vector3.h"               // for Vector3
#include "Debug.h"                // for Debug

using namespace std;
	Game::Game()
	{
		
	}
	Mat4x4 m, v, p, MVP;
	Shader* activeShader;
	Shader reg;
	cModel* activeModel;
	cModel testModel, sBox;

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
		input = new Input();
		resources = new Resources();
		Shader::Init();
		cModel::Init();
		reg.CreateProgram("reg", "shaders\\solid_v.glsl", "shaders\\solid_f.glsl");
		reg.AddUniform("MVP");
		reg.AddUniform("bobs");
		testModel.CreateModel("suzanne","suz.obj");
		activeShader = &reg;
		activeShader->Bind();
		pos = { 4,4,4 };
	}
	int zm=5, isize=5;
	bool wf;
	float x, y, z;
	void Game::Update() {
		glClearColor(.85, .85, .85, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		
		m.Identity();
		p.Perspective(90,1, 0.1f, 200);
		v.View({ pos.x,pos.y,pos.z }, { tar.x, tar.y, tar.z }, { 0, 1, 0 });
		m.Identity();
		MVP = m*v*p;
		activeShader->SetUniform("MVP", MVP);
		activeShader->SetUniform("bobs", { .4f,.4f,.4f });
		Debug::DrawGrid(5);

		m.Identity();
		MVP = m*v*p;
		activeModel = &testModel;
		activeShader->SetUniform("MVP", MVP);
		activeShader->SetUniform("bobs", { 1,0,0 });
		activeModel->Draw();

		
		m.Translate(tar);
		m.Scale(.1f, .1f, .1f);
		MVP = m*v*p;
		activeShader->SetUniform("MVP", MVP);
		activeShader->SetUniform("bobs", { 1,0,1 });
		Debug::DrawWireSphere({ 0,0,0 });

	}
