#pragma once
#include "Maths.h"
#include "Transform.h"
#include "Model.h"
namespace MGLE {
	class GameObject
	{
		cModel m;
		tString mName;
		Transform transform;
	public:
		GameObject(tString asName,tString asModelFile);
		void Render();
		~GameObject();
	};
}

