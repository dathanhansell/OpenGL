#pragma once
#include "Timer.h"  // for Timer
#include<SFML/Graphics.hpp>
#include "GL/glew.h"                       
#include "iosfwd"                          
#include "iostream"                        
#include "LowLevelSystem.h"                
#include "ostream"                         
#include "Renderer.h"                      
#include "SFML/Graphics/RenderWindow.hpp"  
#include "SFML/Window/ContextSettings.hpp" 
#include "SFML/Window/VideoMode.hpp"       
#include "SFML/Window/WindowStyle.hpp"     
#include "vcruntime_new.h"                 
#include <string>     
	//class Window;
	class Renderer;
	class Graphics
	{
		
		Renderer* renderer;
		Timer frameTimer;
		int frameCount;
		bool InitGL();
		bool InitGLEW();
		void Render();
		sf::RenderWindow* window;
		void Init();
	public:
		void FPS();
		//Window* window;
		Graphics();
		~Graphics();

	};
