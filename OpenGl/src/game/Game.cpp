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
	}
	void Game::Update() {
		glClearColor(.85, .85, .85, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
