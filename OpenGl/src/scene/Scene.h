#pragma once
#include "GameObject.h"
#include "Camera.h"
#include "Maths.h"
namespace MGLE {
	class Scene
	{
		Camera mCamera;
	public:
		Camera& GetCamera();
		Scene();
		~Scene();
	};
}

