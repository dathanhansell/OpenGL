#pragma once
#include "GameObject.h"
#include "Camera.h"
#include "Maths.h"
#include "Tree.h"

	class Scene
	{
		Tree<GameObject> Hierarchy;
		Camera mCamera;
	public:
		Camera& GetCamera();
		Scene();
		~Scene();
	};


