#include "Window.h"
namespace MGLE {
	void Window::Reshape(int w, int h) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glViewport(0, 0, w, h);
		gluPerspective(90.0f, (GLfloat)w / h, 0.1, 100);
		width = w; height = h;
		glMatrixMode(GL_MODELVIEW);
	}
	void Window::Init() {
		  // Request 2 levels of antialiasing
		Log( "Creating Window...\n" );
		
		width = 800;
		height = 800;
		sf::ContextSettings settings;
		settings.depthBits = 24;
		settings.stencilBits = 8;
		settings.antialiasingLevel = 4;
		settings.majorVersion = 4;
		settings.minorVersion = 4;
		Log("Initializing OpenGL %i%s%i%s", settings.majorVersion, ".", settings.minorVersion, "...\n");
		window = new sf::Window(sf::VideoMode(width, height, 32), "SFML Window", sf::Style::Default, settings);
	}
	void Window::ResetWindow() {
		glutReshapeWindow(width, height);
		glutPositionWindow(0, 0);
	}
	Window::Window() {
		Init();
	}
	Window::~Window() {
		window->close();
		window->~Window();
	}
	int Window::GetHeight() {
		return height;
	}

	int Window::GetWidth() {
		return width;
	}

	bool Window::Open() {
		return window->isOpen();
	}

	void Window::PollEvents() {
		sf::Event e;
		while (window->pollEvent(e)) {

			if (e.type == sf::Event::Closed)
				window->close();
			if (e.type == sf::Event::Resized)
			{
				Reshape(e.size.width, e.size.height);
			}
		}
	}
	void Window::Display() {
		window->display();
		
	}
}