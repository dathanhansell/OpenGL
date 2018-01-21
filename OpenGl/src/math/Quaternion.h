#pragma once
#include "stdafx.h"
#include "Vector3.h"
#include "Mat4x4.h"
	class Quaternion {
	public:
		float x, y, z, w;
		Quaternion();
		Quaternion(float X, float Y, float Z, float W);
		Quaternion(Mat4x4 mat);
		Quaternion(Vector3 angle);
		Vector3 ToEuler();
		Quaternion& Rotate(Vector3 angle);
		Quaternion& Rotate(float X, float Y, float Z);
		void Normalize();
		std::string ToString();
		void Print(std::string title = "");
	};
