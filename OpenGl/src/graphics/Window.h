#pragma once
#include <stdafx.h>
#include <MGLE.h>
#include<SFML/Window.hpp>
class Window {
	int height;
	int width;
	std::string title = "Game";
	sf::Window window;
	bool fullscreen;
	void Init();
	void ResetWindow();
	
public:
	Window();
	~Window();
	int GetWidth();
	int GetHeight();
	bool Open();
	void PollEvents();
	void Display();
	void Reshape(int w, int h);

};