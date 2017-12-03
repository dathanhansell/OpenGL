#define _USE_MATH_DEFINES
#include "Camera.h"
#include <GL/glut.h>
#include <iostream>
#include <math.h>

Camera::Camera(Vector2 Rotation, Vector3 Position)
{
	rotation = Rotation;
	position = Position;
}

Camera::~Camera()
{

}

void Camera::SetCursorLockState(bool isLocked) 
{
	lockedCursor = isLocked;
}
bool Camera::lockedCursor = false;

void Camera::Render() {
	Maths::Clamp(rotation.y, 89, -89);
	Maths::Eulerize(rotation.x);
	forward = Vector3::forward;
	forward = Vector3::EulerToForwardVector({rotation.x,rotation.y,0});
	up = Vector3::up;
	up = Vector3::EulerToForwardVector({ rotation.x,rotation.y + 90,0 });
	right = Vector3::Cross(up,forward);
	gluLookAt(position.x, position.y, position.z,
		forward.x + position.x, forward.y + position.y, forward.z + position.z,
		0.0, 1.0, 0.0);
}

///////////
//Get
///////////
void Camera::ToggleThirdperson() {
	thirdPerson = !thirdPerson;
}
bool Camera::GetCursorLockState() 
{
	return lockedCursor;
}
Vector3 Camera::GetPosition()
{
	return position;
}
Vector2 Camera::GetRotation()
{
	return rotation;
}
///////////
//Set
///////////
void Camera::SetPosition(Vector3 Position)
{
	position = Position;
}
void Camera::SetRotation(Vector2 Rotation)
{
	rotation = Rotation;
}
