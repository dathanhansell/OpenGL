#include "Graphics.h"
                     
using namespace std;
	Graphics::Graphics()
	{
		Init();
	}

	Graphics::~Graphics()
	{
		delete renderer;
		
		//delete window;
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
		

	}
	
	void Graphics::Init()
	{
		Log("Initializing Graphics Module...\n");
		OpenBar();
		bool fullscreen = false;
		if (!InitGL())
		{
			FatalError("OpenGL Failed To Initialize For Some Reason\n");
			return;
		}
		
		Log("Initializing GLEW...\n");
		if (!InitGLEW())
		{
			FatalError("GLEW Failed To Initialize For Some Reason\n");
			return;
		}
		Log("Creating Renderer...\n");
		renderer = new Renderer();
		Log("Done!\n");
		CloseBar();
	}

	bool Graphics::InitGL()
	{
		Log("Creating SFML Window/Context...\n");

		int width = 800;
		int height = 800;

		sf::ContextSettings settings;
		settings.depthBits = 24;
		settings.stencilBits = 8;
		settings.antialiasingLevel = 4;
		settings.majorVersion = 4;
		settings.minorVersion = 4;

		Log("Initializing OpenGL %i%s%i%s", settings.majorVersion, ".", settings.minorVersion, "...\n");
		//window = new sf::RenderWindow(sf::VideoMode(width, height, 32), "Game", sf::Style::Default, settings);
		
		
		//window = new Window();
		return true;
	}

	bool Graphics::InitGLEW() {
		glewExperimental = GL_TRUE;
		GLenum glewError = glewInit();
		if (glewError != GLEW_OK)
		{
			FatalError("GLEW Init Did Not Return GLEW_OK %s\n", glewGetErrorString(glewError));
			return false;
		}
		return true;
	}


