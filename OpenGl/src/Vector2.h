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
	static float Dot(Vector2 v1, Vector2 v2);
	Vector2 normalized();
	float magnitude();
	void print();
	void print(char* title);
	std::string ToString();
	static Vector2 zero;
};