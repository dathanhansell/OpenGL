#include "Graphics.h"

using namespace std;
namespace MGLE {
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

		Log("Initializing Graphics Module...\n");
		Log("--------------------------------------------------------\n");

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
		Log("--------------------------------------------------------\n");

	}

	bool Graphics::InitGL()
	{
		context.setActive(true);
		Log("Initializing OpenGL %i%s%i%s", context.getSettings().majorVersion, ".", context.getSettings().minorVersion, "...\n");
		window = new Window();
		return true;
	}

	bool Graphics::InitGLEW() {

		glewExperimental = GL_TRUE;
		GLenum glewError = glewInit();
		if (glewError != GLEW_OK)
		{
			FatalError("GLEW Init Did Not Return GLEW_OK\n");
			return false;
		}
		return true;
	}


}