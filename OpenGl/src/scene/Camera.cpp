#include "Camera.h"
#include "Window.h"
#include <math.h>
	Camera::Camera()
	{
	}

	Camera::~Camera()
	{
	}

	Mat4x4& Camera::GetViewMatrix() {
		return mView.View(mTransform.GetPosition(), mTransform.GetPosition() + Vector3::EulerToForwardVector(mTransform.GetRotation()), { 0,1,0 });
	}

	Mat4x4& Camera::GetProjectionMatrix() {
		return mProjection.Perspective(mFov,Window::GetWidth()/ Window::GetHeight(),mNear,mFar);
	}
	
	Transform& Camera::GetTransform() {
		return mTransform;
	}
