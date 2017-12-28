#pragma once
#include "Maths.h"
namespace MGLE {
	class Transform
	{
		Mat4x4 mModel;
		Vector3 mPosition;
		Vector3 mRotation;
		Vector3 mScale;
	public:
		Mat4x4& GetModelMatrix();
		Vector3& GetPosition();
		Vector3& GetRotation();
		Vector3& GetScale();
		void SetPosition(Vector3 position);
		void SetPosition(float x,float y,float z);
		void SetRotation(Vector3 rotation);
		void SetRotation(float x, float y, float z);
		void SetScale(Vector3 scale);
		void SetScale(float x, float y, float z);
		Transform();
		~Transform();
	};
}

