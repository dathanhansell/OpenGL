#pragma once
#include "GameObject.h"
#include "Camera.h"
#include "Maths.h"

	class Scene
	{
		Camera mCamera;
	public:
		Camera& GetCamera();
		Scene();
		~Scene();
	};


