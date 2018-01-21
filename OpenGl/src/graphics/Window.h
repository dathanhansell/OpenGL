#pragma once
#include <stdafx.h>
#include <MGLE.h>
#include<SFML/Window.hpp>
	class Window {
		static int height;
		static int width;
		std::string title = "Game";
		sf::Window* window;
		bool fullscreen;
		void Init();
		void ResetWindow();
	public:
		Window();
		~Window();
		static int GetWidth();
		static int GetHeight();
		sf::Window* GetWindow();
		bool Open();
		void PollEvents();
		void Display();
		void Reshape(int w, int h);

	};
