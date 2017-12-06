#include "Graphics.h"
#include <gl\glew.h>
#include <gl\glut.h>

#include <iostream>
#include <SDL.h>

using namespace std;

	Graphics::Graphics()
	{
		Init();
	}

	Graphics::~Graphics()
	{

	}
	void Update() {

	}
	void Render() {

	}
	void Reshape(int w, int h) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glViewport(0, 0, w, h);
		gluPerspective(90.0f, (GLfloat)w / h, 0.1, 100);
		glMatrixMode(GL_MODELVIEW);
	}
	void Graphics::Init()
	{
		width = 1280;
		height = 720;
		bool fullscreen = false;
		cout << "Initializing OpenGL..." << endl;
		if (!InitGL())
		{gggggggg
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Initialize Error", "Unable to initialize OpenGL!", NULL);
			return;
		}
		cout << "Initializing GLEW..." << endl;
		if (!InitGLEW())
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Initialize Error", "Unable to initialize GLEW!", NULL);
			return;
		}
		glutReshapeFunc(Reshape);
		glutIdleFunc(Update);
<<<<<<< HEAD
		//glutDisplayFunc(Render);
=======
		glutDisplayFunc(Render);
>>>>>>> 629832113a54c57b774468ecd427e6aafed3b83d
		glutMainLoop();
	}

	bool Graphics::InitGL()
	{
		glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
		glutInitWindowSize(width, height);
		glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - width) / 2,
			(glutGet(GLUT_SCREEN_HEIGHT) - height) / 2);
		glutCreateWindow("OpenGl");

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(90.0f, (GLfloat)width / height, 0.1, .2);
		glMatrixMode(GL_MODELVIEW);
		return true;
	}

	bool Graphics::InitGLEW() {

		glewExperimental = GL_TRUE;
		GLenum glewError = glewInit();
		if (glewError != GLEW_OK)
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Initialize Error", "Couldn't initialize Glew", NULL);
		}
		return true;
	}
	void Graphics::ResetWindow() {
		glutReshapeWindow(width, height);
		glutPositionWindow(0, 0);
	}

