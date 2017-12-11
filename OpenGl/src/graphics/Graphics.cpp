#include "Graphics.h"

using namespace std;

	Graphics::Graphics()
	{
		Init();
	}

	Graphics::~Graphics()
	{
		delete renderer;
		delete window;
	}
	void Graphics::FPS() {
		if (frameTimer.IsRunning() && frameTimer.ElapsedMilliseconds() >= 1000)
		{
			cout << "FPS: " << frameCount << endl;
			frameCount = 0;
			frameTimer.Stop();
			frameTimer.Start();
		}
		else if (!frameTimer.IsRunning()) frameTimer.Start();
	}
	void Graphics::Render() {	
		FPS();
		glClearColor(.1f, .1f, .1f, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		Debug::DrawWireSphere(Vector3::zero);
		glutSwapBuffers();
		
	}

	void Graphics::Init()
	{
		
		cout << "Initializing Graphics Module..." << endl;
		
		bool fullscreen = false;
		cout << "Initializing OpenGL " << context.getSettings().majorVersion << "." << context.getSettings().minorVersion << "..."<<endl;

		if (!InitGL())
		{
			return;
		}
		
		cout << "Initializing GLEW..." << endl;
		if (!InitGLEW())
		{
			return;
		}
		cout << "Creating Renderer..." << endl;
		renderer = new Renderer();
		cout << "Done!" << endl;

	}

	bool Graphics::InitGL()
	{
		context.setActive(true);
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
	

