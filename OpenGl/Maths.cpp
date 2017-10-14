#include "Maths.h"
#include <string>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <sstream>

Vector2::Vector2()
{
	x = 0;
	y = 0;
}
Vector2::Vector2(float X, float Y)
{
	x = X;
	y = Y;
}
Vector2& Vector2::operator+(const Vector2& a)
{
	return Vector2(a.x + x, a.y + y);
}
Vector2& Vector2::operator-(const Vector2& a)
{
	return Vector2(x - a.x, y - a.y);
}
Vector2& Vector2::operator*(const Vector2& a)
{
	return Vector2(a.x * x, a.y * y);
}
Vector2& Vector2::operator+=(const Vector2& a)
{
	x += a.x;
	y += a.y;
	return *this;
}
Vector2& Vector2::operator*=(const Vector2& a)
{
	x *= a.x;
	y *= a.y;
	return *this;
}
bool Vector2::operator!=(const Vector2& a)
{
	return x != a.x || y != a.y;
}
Vector2& Vector2::operator-() const {
	return Vector2(-x, -y);
}
Vector2& Vector2::operator*(const float& a)
{
	return Vector2(x * a, y * a);
}
Vector2& Vector2::operator/(const float& a)
{
	return Vector2(x / a, y / a);
}
Vector2& Vector2::operator*=(const float& a)
{
	x *= a;
	y *= a;
	return *this;
}
void Vector2::Normalize()
{
	float m = sqrt(x * x + y * y);
	x /= m;
	y /= m;
}
Vector2 Vector2::normalized()
{
	float m = sqrt(x * x + y * y);
	return Vector2(x / m, y / m);
}
float Vector2::magnitude()
{
	return sqrt(x * x + y * y);
}
void Vector2::print()
{
	std::cout << "X: " << x << " Y: " << y << std::endl;
}
void Vector2::print(char* title)
{
	std::cout << title << "X: " << x << " Y: " << y << std::endl;
}
std::string Vector2::ToString()
{
	std::ostringstream buffer;
	buffer << "X: " << x << " Y: " << y;
	return buffer.str();
}
Vector2 Vector2::zero = { 0,0 };

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
	return Vector3(-x, -y, -z);
}
Vector3& Vector3::operator*(const float& a)
{
	return Vector3(x * a, y * a, z * a);
}
Vector3& Vector3::operator/(const float& a)
{
	return Vector3(x / a, y / a, z / a);
}
Vector3& Vector3::operator*=(const float& a)
{
	x *= a;
	y *= a;
	z *= a;
	return *this;
}
Vector3 Vector3::EulerToForwardVector(Vector3 Rotation){
	Rotation *= M_PI / 180.0;
	return Vector3(-sin(Rotation.x)* cos(Rotation.y), sin(Rotation.y), cos(Rotation.x) * cos(Rotation.y));
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
	std::cout <<title<< "X: " << x << " Y: " << y << " Z: " << z << std::endl;
}
std::string Vector3::ToString()
{
	std::ostringstream buffer;
	buffer << "X: " << x << " Y: " << y << " Z: " << z;
	return buffer.str();
}
Vector3 Vector3::zero = { 0,0,0 };
Vector3 Vector3::up = { 0,1,0 };
Vector3 Vector3::right = { 1,0,0 };
Vector3 Vector3::forward = { 0,0,1 };
void Maths::Clamp(float& in, float max, float min){
	if (in >= max) in = max;
	if (in <= min) in = min;
}
void Maths::Eulerize(float& in){
	if (in >= 360) in -= 360;
	if (in <= 0) in += -in + 360;
}