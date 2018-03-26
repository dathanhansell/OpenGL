#include "Game.h"
#include "Graphics.h"              // for Graphics
#include "Input.h"                 // for Input
#include "LowLevelSystem.h"        // for Log, CloseBar, OpenBar
#include "Model.h"                 // for cModel
#include "Resources.h"             // for Resources
#include "Shader.h"                // for Shader
#include "vcruntime_new.h"         // for operator delete, operator new
#include "Vector3.h"               // for Vector3
#include "GL/glew.h"         // for glClear, glClearColor, GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT

using namespace std;
	Game::Game()
	{
		
	}

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
		glClearColor(1,0,1, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glColor3f(0,0,0);
		Debug::DrawWireSphere(Vector3::zero);
	}
