#include "Scene.h"

namespace MGLE {

	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}
	Camera& Scene::GetCamera() {
		return mCamera;
	}
}