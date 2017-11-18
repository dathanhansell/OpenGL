#include "Maths.h"
#include <string>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <sstream>
const float DEG2RAD = 3.141593f / 180.0f;
const float RAD2DEG = 180.0f / 3.141593f;
const float EPSILON = 0.00001f;
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
float Vector2::Dot(Vector2 v1, Vector2 v2) {
	return v1.x * v2.x + v1.y * v2.y;
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

Mat4x4::Mat4x4() {

}
Mat4x4::Mat4x4(const float src[16]) {

}
Mat4x4::Mat4x4(float m00, float m01, float m02, float m03,
	float m04, float m05, float m06, float m07,
	float m08, float m09, float m10, float m11,
	float m12, float m13, float m14, float m15) {

}
Mat4x4& Mat4x4::translate(const Vector3& v)
{
	return translate(v.x, v.y, v.z);
}

Mat4x4& Mat4x4::translate(float x, float y, float z)
{
	m[0] += m[3] * x;   m[4] += m[7] * x;   m[8] += m[11] * x;   m[12] += m[15] * x;
	m[1] += m[3] * y;   m[5] += m[7] * y;   m[9] += m[11] * y;   m[13] += m[15] * y;
	m[2] += m[3] * z;   m[6] += m[7] * z;   m[10] += m[11] * z;   m[14] += m[15] * z;

	return *this;
}

Mat4x4& Mat4x4::scale(float s)
{
	return scale(s, s, s);
}

Mat4x4& Mat4x4::scale(float x, float y, float z)
{
	m[0] *= x;   m[4] *= x;   m[8] *= x;   m[12] *= x;
	m[1] *= y;   m[5] *= y;   m[9] *= y;   m[13] *= y;
	m[2] *= z;   m[6] *= z;   m[10] *= z;   m[14] *= z;
	return *this;
}
/*
Mat4x4& Mat4x4::rotate(Vector3 angle)
{
	return rotate(angle.x, angle.y, angle.z);
}

Mat4x4& Mat4x4::rotate(float x, float y, float z)
{
	float c = 0;
	float s = 0;
	//float c = cosf(angle * DEG2RAD);    
	//float s = sinf(angle * DEG2RAD);    
	float c1 = 1.0f - c;                
	float m0 = m[0], m4 = m[4], m8 = m[8], m12 = m[12],
		m1 = m[1], m5 = m[5], m9 = m[9], m13 = m[13],
		m2 = m[2], m6 = m[6], m10 = m[10], m14 = m[14];

	// build rotation matrix
	float r0 = x * x * c1 + c;
	float r1 = x * y * c1 + z * s;
	float r2 = x * z * c1 - y * s;
	float r4 = x * y * c1 - z * s;
	float r5 = y * y * c1 + c;
	float r6 = y * z * c1 + x * s;
	float r8 = x * z * c1 + y * s;
	float r9 = y * z * c1 - x * s;
	float r10 = z * z * c1 + c;

	// multiply rotation matrix
	m[0] = r0 * m0 + r4 * m1 + r8 * m2;
	m[1] = r1 * m0 + r5 * m1 + r9 * m2;
	m[2] = r2 * m0 + r6 * m1 + r10* m2;
	m[4] = r0 * m4 + r4 * m5 + r8 * m6;
	m[5] = r1 * m4 + r5 * m5 + r9 * m6;
	m[6] = r2 * m4 + r6 * m5 + r10* m6;
	m[8] = r0 * m8 + r4 * m9 + r8 * m10;
	m[9] = r1 * m8 + r5 * m9 + r9 * m10;
	m[10] = r2 * m8 + r6 * m9 + r10* m10;
	m[12] = r0 * m12 + r4 * m13 + r8 * m14;
	m[13] = r1 * m12 + r5 * m13 + r9 * m14;
	m[14] = r2 * m12 + r6 * m13 + r10* m14;

	return *this;
}
*/
Vector3& Mat4x4::rotate(Vector3 angle)
{
	Vector3 f = Vector3::forward;
	Vector3 r = Vector3::right;
	Vector3 u = Vector3::up;

	f = Vector3::EulerToForwardVector(angle);
	r = Vector3::Cross(u, f).normalized();
	u = Vector3::Cross(f, r);

	//m[0] = cos(x) * -sin(y)
	return Vector3(0,0,0);
}