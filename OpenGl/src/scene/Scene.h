#pragma once

#include "Camera.h"
#include "Tree.h"

	class Scene
	{
		
		Camera mCamera;
	public:
		Camera& GetCamera();
		Tree Hierarchy;
		Scene();
		~Scene();
	};


