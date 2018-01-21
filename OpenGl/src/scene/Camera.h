#pragma once
#include "Transform.h"
	class Camera
	{
		Transform mTransform;
		Mat4x4 mView, mProjection;
		float mFov = 45.0f, mNear = .01f, mFar = 50.0f;
	public:
		Mat4x4& GetViewMatrix();
		Mat4x4& GetProjectionMatrix();
		Transform& GetTransform();
		//TODO getters and setters
		Camera();
		~Camera();
	};


