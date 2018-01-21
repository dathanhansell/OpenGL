#include "Window.h"
	void Window::Reshape(int w, int h) {
		glViewport(0, 0, w, h);
		width = w; height = h;
	}
	int Window::height = 800;
	int Window::width = 800;
	void Window::Init() {
		  // Request 2 levels of antialiasing
		Log( "Creating SFML Window/Context...\n" );
		
		width = 800;
		height = 800;
		
		sf::ContextSettings settings;
		settings.depthBits = 24;
		settings.stencilBits = 8;
		settings.antialiasingLevel = 4;
		settings.majorVersion = 4;
		settings.minorVersion = 4;
		
		Log("Initializing OpenGL %i%s%i%s", settings.majorVersion, ".", settings.minorVersion, "...\n");
		window = new sf::Window(sf::VideoMode(width, height, 32), "Game", sf::Style::Default, settings);
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
	sf::Window* Window::GetWindow() {
		return window;
	}
	void Window::PollEvents() {
		
	}
	void Window::Display() {
		window->display();
		
	}
