#include "Vector3.h"
#include <string>
#include <iostream>
#include <math.h>
#include <sstream>
const float DEG2RAD = 3.141593f / 180.0f;
const float RAD2DEG = 180.0f / 3.141593f;
const float EPSILON = 0.00001f;
Vector3::Vector3()
{
	x = 0;
	y = 0;
	z = 0;
}
Vector3::Vector3(float X, float Y, float Z)
{
	x = X;
	y = Y;
	z = Z;
}
Vector3& Vector3::operator+(const Vector3& a)
{
	return Vector3(a.x + x, a.y + y, a.z + z);
}
Vector3& Vector3::operator-(const Vector3& a)
{
	return Vector3(x - a.x, y - a.y, z - a.z);
}
Vector3& Vector3::operator*(const Vector3& a)
{
	return Vector3(a.x * x, a.y * y, a.z * z);
}

Vector3& Vector3::operator+=(const Vector3& a)
{
	x += a.x;
	y += a.y;
	z += a.z;
	return *this;
}
Vector3& Vector3::operator*=(const Vector3& a)
{
	x *= a.x;
	y *= a.y;
	z *= a.z;
	return *this;
}
Vector3& Vector3::operator-() const {
	Vector3 tmp;
	tmp.x = -tmp.x;
	tmp.y = -tmp.y;
	tmp.z = -tmp.z;
	return tmp;
}
Vector3& Vector3::operator*(const float& a)
{
	return Vector3(x * a, y * a, z * a);
}
Vector3& Vector3::operator/(const float& a)
{
	if (a == 0) return *this;
	return Vector3(x / a, y / a, z / a);
}
Vector3& Vector3::operator*=(const float& a)
{
	x *= a;
	y *= a;
	z *= a;
	return *this;
}

Vector3 Vector3::Cross(Vector3 a, Vector3 b) {
	Vector3 v;
	v.x = (a.y*b.z) - (a.z*b.y);
	v.y = (a.z*b.x) - (a.x*b.z);
	v.z = (a.x*b.y) - (a.y*b.x);
	return v;
}
void Vector3::Normalize()
{
	float m = sqrt(x * x + y * y + z * z);
	x /= m;
	y /= m;
	z /= m;
}
float Vector3::Dot(Vector3 v1, Vector3 v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
Vector3 Vector3::normalized()
{
	float m = sqrt(x * x + y * y + z * z);
	return Vector3(x / m, y / m, z / m);
}
float Vector3::magnitude()
{
	return sqrt(x * x + y * y + z * z);
}
void Vector3::print()
{
	std::cout << "X: " << x << " Y: " << y << " Z: " << z << std::endl;
}
void Vector3::print(char* title)
{
	std::cout << title << "X: " << x << " Y: " << y << " Z: " << z << std::endl;
}
std::string Vector3::ToString()
{
	std::ostringstream buffer;
	buffer << "X: " << x << " Y: " << y << " Z: " << z;
	return buffer.str();
}

Vector3 Vector3::EulerToForwardVector2(Vector3 r) {
	r *= DEG2RAD;
	return Vector3(cos(r.x) * cos(r.x)* -sin(r.y) * sin(r.z),
		sin(r.x) * cos(r.y) * cos(r.y) * -sin(r.z),
		-sin(r.x) * sin(r.y) * cos(r.z) *  cos(r.z));

}

Vector3 Vector3::EulerToForwardVector(Vector3 r) {
	r *= DEG2RAD;
	return Vector3(-sin(r.x)* cos(r.y),
		sin(r.y),
		cos(r.x) * cos(r.y));
}
Vector3 Vector3::zero = { 0,0,0 };
Vector3 Vector3::up = { 0,1,0 };
Vector3 Vector3::right = { 1,0,0 };
Vector3 Vector3::forward = { 0,0,1 };
