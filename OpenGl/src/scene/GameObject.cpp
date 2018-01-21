#include "GameObject.h"

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
