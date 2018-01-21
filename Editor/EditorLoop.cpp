#include "stdafx.h"
#include "EditorLoop.h"


	EditorLoop::EditorLoop()
	{
		m_game.Init();
	}
	void EditorLoop::Update() {
		
		m_game.Update();
		
	}

