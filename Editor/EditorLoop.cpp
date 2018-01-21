#include "stdafx.h"
#include "EditorLoop.h"


	EditorLoop::EditorLoop()
	{
		
	}
	void EditorLoop::Start() {
		m_game = new Game();
	}
	void EditorLoop::Update() {
		
		m_game->Update();
		
	}

