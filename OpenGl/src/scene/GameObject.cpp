#include "GameObject.h"

namespace MGLE {

	GameObject::GameObject(tString asName, tString asModelFile)
	{
		mName = asName;
		m.CreateModel(asName, asModelFile);
	}
	void GameObject::Render() {
		transform.GetModelMatrix();

	}

	GameObject::~GameObject()
	{
	}


}