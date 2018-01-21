#include "Transform.h"

	Transform::Transform()
	{
	}

	Transform::~Transform()
	{
	}

	Mat4x4& Transform::GetModelMatrix() {
		mModel.Identity();
		mModel.Scale(mScale.x, mScale.y, mScale.z);
		mModel.rotate(mRotation.x, { 1,0,0 });
		mModel.rotate(mRotation.y, { 0,1,0 });
		mModel.rotate(mRotation.z, { 0,0,1 });
		mModel.Translate(mPosition);
		
		return mModel;
	}

	Vector3& Transform::GetPosition(){
		return mPosition;
	}
	Vector3& Transform::GetRotation() {
		return mRotation;
	}
	Vector3& Transform::GetScale() {
		return mScale;
	}
	void Transform::SetPosition(Vector3 position) {
		SetPosition(position.x, position.y, position.z);
	}
	void Transform::SetPosition(float x, float y, float z) {
		mPosition.x = x; mPosition.y; mPosition.z;
	}
	void Transform::SetRotation(Vector3 rotation) {
		SetPosition(rotation.x, rotation.y, rotation.z);
	}
	void Transform::SetRotation(float x, float y, float z) {
		mRotation.x = x; mRotation.y; mRotation.z;
	}
	void Transform::SetScale(Vector3 scale) {
		SetPosition(scale.x, scale.y, scale.z);
	}
	void Transform::SetScale(float x, float y, float z) {
		mScale.x = x; mScale.y; mScale.z;
	}
