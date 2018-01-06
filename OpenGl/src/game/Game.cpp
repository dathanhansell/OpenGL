#include "Game.h"
#include "GameObject.h"
#include <stdio.h>
#include <iostream>
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION    
#include "stb_image.h"
using namespace std;
namespace MGLE {
	Game::Game()
	{
		Init();
	}
	Mat4x4 m, v, p, MVP;
	Shader* activeShader;
	Shader reg, err, bas;
	cModel* activeModel;
	cModel suz, mon;

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
	GLuint texture;
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

		err.CreateProgram("error", "shaders\\error_v.glsl", "shaders\\error_f.glsl");
		err.AddUniform("MVP");

		bas.CreateProgram("bas", "shaders\\vert.glsl", "shaders\\frag.glsl");
		bas.AddUniform("MVP");
		bas.AddUniform("tDiffuse");
		activeShader = &reg;
		mon.CreateModel("sphere", "uvCube.obj");
		suz.CreateModel("suzanne", "wrong_on_purpose.butts");
		activeModel = &suz;
		pos = { 0,0,4 };
		
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// load and generate the texture
		int width, height, nrChannels;
		string path = GetAbsolutePath() + "bottfle.png";
		unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			Error("Failed to load texture\n");
		}
		stbi_image_free(data);
	}
	float x, y, zm = 5;
	int size = 5;
	bool wf;
	
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
		p.Perspective(45, (float)graphics->window->GetWidth() / (float)graphics->window->GetHeight(), 0.1f, 200);
		//p.Orthographic(-.05,.05,-.05,.05,.1,100);
		v.View({ pos.x,pos.y,pos.z }, { tar.x, tar.y, tar.z }, { 0, 1, 0 });
		m.Translate(0, 0, -5);
		MVP = m*v*p;
		activeModel = &suz;
		activeShader = &err;
		activeShader->Bind();
		activeShader->SetUniform("MVP", MVP);
		activeModel->Draw();

		m.Identity();
		m.Translate(0, 0, 0);
		MVP = m*v*p;
		activeModel = &mon;
		activeShader = &bas;
		activeShader->Bind();
		activeShader->SetUniform("MVP", MVP);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		activeShader->SetUniform("tDiffuse", 0);
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
		input->Update();
		
		graphics->window->Display();
	}
}