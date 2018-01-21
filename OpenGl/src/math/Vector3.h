#pragma once
#include <string>
	class Vector3
	{
	public:
		float x, y, z;
		Vector3();
		Vector3(float X, float Y, float Z);
		Vector3& operator+(const Vector3& a);
		Vector3& operator-(const Vector3& a);
		Vector3& operator*(const Vector3& a);
		Vector3& operator+=(const Vector3& a);
		Vector3& operator*=(const Vector3& a);
		Vector3 operator-() const;
		Vector3& operator*(const float& a);
		Vector3& operator/(const float& a);
		Vector3& operator*=(const float& a);
		void Normalize();
		Vector3 normalized();
		static Vector3 EulerToForwardVector(Vector3 Rotation);
		static Vector3 EulerToForwardVector2(Vector3 Rotation);
		static Vector3 Cross(Vector3 a, Vector3 b);
		static float Dot(Vector3 v1, Vector3 v2);
		float magnitude();
		void print();
		void print(char* title);
		std::string ToString();
		static Vector3 zero;
		static Vector3 up;
		static Vector3 right;
		static Vector3 forward;
	};

