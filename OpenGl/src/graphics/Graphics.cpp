#include "Graphics.h"

using namespace std;

	Graphics::Graphics()
	{
		Init();
	}

	Graphics::~Graphics()
	{

		delete window;
	}
	void Update() {
		//SDL_Delay(16.6667);
	}
	void Graphics::Render() {
		cout << "Elapsed Ms: " << frameTimer.ElapsedMilliseconds() << endl;
		cout << "Running: " << frameTimer.IsRunning() << endl;
		if (frameTimer.IsRunning() && frameTimer.ElapsedMilliseconds() >= 1000)
		{
			cout << "Elapsed Ms: " << frameTimer.ElapsedMilliseconds() << endl;
			cout << "FPS: " << frameCount << endl;
			frameCount = 0;
			frameTimer.Stop();
			frameTimer.Start();
		}
		else frameTimer.Start();
		glClearColor(.1f, .1f, .1f, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		Debug::DrawWireSphere(Vector3::zero);
		glutSwapBuffers();
		frameCount++;
	}
	Graphics* instance;
	void Graphics::RenderCallBack() {
		instance->Render();
	}
	
	void Graphics::Init()
	{
		cout << "Initializing Graphics Module..." << endl;
		
		bool fullscreen = false;
		cout << "Initializing OpenGL..." << endl;
		if (!InitGL())
		{
			return;
		}
		cout << "Initializing GLEW..." << endl;
		if (!InitGLEW())
		{
			return;
		}
		instance = this;
		glutIdleFunc(Update);
		::glutDisplayFunc(Graphics::RenderCallBack);
		glutMainLoop();
		cout << "Done!" << endl;
	}

	bool Graphics::InitGL()
	{
		window = new Window();
		return true;
	}

	bool Graphics::InitGLEW() {

		glewExperimental = GL_TRUE;
		GLenum glewError = glewInit();
		if (glewError != GLEW_OK)
		{

		}
		return true;
	}
	

