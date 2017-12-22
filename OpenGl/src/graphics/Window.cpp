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
		Log( "Creating Window...\n" );
		width = 800;
		height = 800;
		window.create(sf::VideoMode(width, height), title);
		glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	}
	void Window::ResetWindow() {
		glutReshapeWindow(width, height);
		glutPositionWindow(0, 0);
	}
	Window::Window() {
		Init();
	}
	Window::~Window() {
		window.close();
		window.~Window();
	}
	int Window::GetHeight() {
		return height;
	}

	int Window::GetWidth() {
		return width;
	}

	bool Window::Open() {
		return window.isOpen();
	}

	void Window::PollEvents() {
		sf::Event e;
		while (window.pollEvent(e)) {

			if (e.type == sf::Event::Closed)
				window.close();
			if (e.type == sf::Event::Resized)
			{
				Reshape(e.size.width, e.size.height);
			}
		}
	}
	void Window::Display() {
		window.display();
	}
}