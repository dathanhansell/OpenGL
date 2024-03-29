// Game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <MGLE.h>
#include "imgui/imgui.h"
#include "imgui/imgui-sfml.h"

#include <SFML/System.hpp>

using namespace MGLE;
Game* mGame;
	int main(int argc, char** argv)
	{
		glutInit(&argc, argv);
		mGame = new Game();

		//ImGui::SFML::Init(mGame->graphics->window->GetWindow());

				//ImGui::SFML::ProcessEvent(event);

		while (mGame->graphics->window->Open()) {
			sf::sleep(sf::microseconds(16667));
			mGame->Update();
			//ImGui::SFML::Update(deltaClock.restart());
			ImGui::Begin("Sample window");
			ImGui::End();
			ImGui::Render();
			mGame->graphics->window->PollEvents();
			mGame->graphics->window->Display();
		}
		delete mGame;
		ImGui::SFML::Shutdown();
		return 0;
	}



