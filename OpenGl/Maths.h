#pragma once
#include <string>
class Vector2
{
public:
	float x, y;
	Vector2();
	Vector2(float X, float Y);
	Vector2& operator+(const Vector2& a);
	Vector2& operator-(const Vector2& a);
	Vector2& operator*(const Vector2& a);
	Vector2& operator+=(const Vector2& a);
	Vector2& operator*=(const Vector2& a);
	Vector2& operator-() const;
	Vector2& operator*(const float& a);
	Vector2& operator/(const float& a);
	Vector2& operator*=(const float& a);
	bool operator!=(const Vector2& a);
	void Normalize();
	Vector2 normalized();
	float magnitude();
	void print();
	void print(char* title);
	std::string ToString();
	static Vector2 zero;
};
class Vector3
{
public:
	float x, y, z;
	Vector3();
	Vector3(float X, float Y,float Z);
	Vector3& operator+(const Vector3& a);
	Vector3& operator-(const Vector3& a);
	Vector3& operator*(const Vector3& a);
	Vector3& operator+=(const Vector3& a);
	Vector3& operator*=(const Vector3& a);
	Vector3& operator-() const;
	Vector3& operator*(const float& a);
	Vector3& operator/(const float& a);
	Vector3& operator*=(const float& a);
	void Normalize();
	Vector3 normalized();
	static Vector3 EulerToForwardVector(Vector3 Rotation);
	static Vector3 Cross(Vector3 a, Vector3 b);
	float magnitude();
	void print();
	void print(char* title);
	std::string ToString();
	static Vector3 zero;
	static Vector3 up;
	static Vector3 right;
	static Vector3 forward;
};
struct Vector4
{
	float x, y, z, w;
	Vector4();
	Vector4(float X, float Y, float Z, float W);
	Vector4 &operator + (Vector4 a);
	Vector4	&operator - (Vector4 a);
	Vector4 &operator * (Vector4 a);
	Vector4 &operator += (Vector4 a);
	Vector4	&operator *= (Vector4 a);
	Vector4	&operator + (float a);
	Vector4	&operator * (float a);
	Vector4	&operator / (float a);
	Vector4	&operator *= (float a);
	inline void normalize();
	inline Vector4 normalized();
	inline float magnitude(Vector4 in);
	inline float magnitude();
	void print();
	std::string ToString();
};
class Maths
{
public:
	static void Clamp(float& in, float max,float min);
	static void Eulerize(float& in);
};
class Mat4x4 {
public:
	/*
	Mat4x4();  // init with identity
	Mat4x4(const float src[16]);
	Mat4x4(float m00, float m01, float m02, float m03, // 1st column
		float m04, float m05, float m06, float m07, // 2nd column
		float m08, float m09, float m10, float m11, // 3rd column
		float m12, float m13, float m14, float m15);// 4th column
		*/
};



