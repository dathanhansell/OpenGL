#pragma once
#include "Maths.h"
class Camera
{
	static bool lockedCursor;
	bool thirdPerson;
public:
	Vector2 rotation;
	Vector3 position;
	Vector3 forward,right,up;
	static void SetCursorLockState(bool isLocked);
	static bool GetCursorLockState();


	Vector3 GetPosition();
	void SetPosition(Vector3 Position);
	Vector2 GetRotation();
	void SetRotation(Vector2 Rotation);
	void ToggleThirdperson();
	void Render();
	
	Camera(Vector2 Rotation, Vector3 Position);
	~Camera();
};

