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
	m[0] = 0; m[4] = 0; m[8] = 0; m[12] = 0;
	m[1] = 0; m[5] = 0;	m[9] = 0; m[13] = 0;
	m[2] = 0; m[6] = 0;	m[10] = 0; m[14] = 0;
	m[3] = 0; m[7] = 0;	m[11] = 0; m[15] = 0;
}
Mat4x4::Mat4x4(const float src[16]) {
	m[0] = src[0]; m[4] = src[4];   m[8]  = src[8];  m[12] = src[12];
	m[1] = src[1]; m[5] = src[5];	m[9]  = src[9];  m[13] = src[13];
	m[2] = src[2]; m[6] = src[6];	m[10] = src[10]; m[14] = src[14];
	m[3] = src[3]; m[7] = src[7];	m[11] = src[11]; m[15] = src[15];
}
Mat4x4::Mat4x4(float m00, float m01, float m02, float m03,
	float m04, float m05, float m06, float m07,
	float m08, float m09, float m10, float m11,
	float m12, float m13, float m14, float m15) {
	m[0] = m00; m[4] = m04;   m[8] = m08;  m[12] = m12;
	m[1] = m01; m[5] = m05;	m[9] = m09;  m[13] = m13;
	m[2] = m02; m[6] = m06;	m[10] = m10; m[14] = m14;
	m[3] = m03; m[7] = m07;	m[11] = m11; m[15] = m15;
}
Mat4x4& Mat4x4::Translate(const Vector3& v)
{
	return Translate(v.x, v.y, v.z);
}
Mat4x4& Mat4x4::Translate(float x, float y, float z)
{
	m[0] += m[3] * x;   m[4] += m[7] * x;   m[8] += m[11] * x;   m[12] += m[15] * x;
	m[1] += m[3] * y;   m[5] += m[7] * y;   m[9] += m[11] * y;   m[13] += m[15] * y;
	m[2] += m[3] * z;   m[6] += m[7] * z;   m[10] += m[11] * z;   m[14] += m[15] * z;

	return *this;
}
Mat4x4& Mat4x4::Scale(float s)
{
	return Scale(s, s, s);
}
Mat4x4& Mat4x4::Scale(float x, float y, float z)
{
	m[0] *= x;   m[4] *= x;   m[8] *= x;   m[12] *= x;
	m[1] *= y;   m[5] *= y;   m[9] *= y;   m[13] *= y;
	m[2] *= z;   m[6] *= z;   m[10] *= z;   m[14] *= z;
	return *this;
}
Mat4x4& Mat4x4::Perspective(float fov, float aspectRatio, float zNear, float zFar)
{
	float tanHalfFOV = (float)tan(fov / 2);
	float zRange = zNear - zFar;

	m[0] = 1.0f / (tanHalfFOV * aspectRatio);	m[4] = 0;		m[8] = 0;	m[12] = 0;
	m[1] = 0;						m[5] = 1.0f / tanHalfFOV;	m[9] = 0;	m[13] = 0;
	m[2] = 0;						m[6] = 0;					m[10] = (-zNear - zFar) / zRange;	m[15] = 2 * zFar * zNear / zRange;
	m[3] = 0;						m[7] = 0;					m[11] = 1;	m[14] = 0;

	return *this;
}
Mat4x4& Mat4x4::Orthographic(float left, float right, float bottom, float top, float near, float far)
{
	float width = right - left;
	float height = top - bottom;
	float depth = far - near;

	m[0] = 2 / width; m[4] = 0;			 m[8] = 0;			 m[12] = -(right + left) / width;
	m[1] = 0;		  m[5] = 2 / height; m[9] = 0;			 m[13] = -(top + bottom) / height;
	m[2] = 0;		  m[6] = 0;		 	 m[10] = -2 / depth; m[14] = -(far + near) / depth;
	m[3] = 0;		  m[7] = 0;			 m[11] = 0;			 m[15] = 1;

	return *this;
}
Mat4x4& Mat4x4::View(Vector3 eye, Vector3 target, Vector3 up)
{
	Vector3 zaxis = (eye - target).normalized();
	Vector3 xaxis = Vector3::Cross(up, zaxis).normalized();
	Vector3 yaxis = Vector3::Cross(zaxis, xaxis).normalized();

	m[0] = xaxis.x;					  m[4] = yaxis.x;					m[8] = zaxis.x;					   m[12] = 0;
	m[1] = xaxis.y;					  m[5] = yaxis.y;					m[9] = zaxis.y,		               m[13] = 0;
	m[2] = xaxis.z;					  m[6] = yaxis.z;					m[10] = zaxis.z,				   m[14] = 0;
	m[3] = -Vector3::Dot(xaxis, eye); m[7] = -Vector3::Dot(yaxis, eye); m[11] = -Vector3::Dot(zaxis, eye); m[15] = 1;

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
Vector3& Mat4x4::Rotate(Vector3 angle)
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
Quaternion::Quaternion() {
	x = 0; y = 0; z = 0; w = 0;
}
Quaternion::Quaternion(float X, float Y, float Z, float W) {
	x = X; y = Y; z = Z; w = W;
}
Quaternion& Quaternion::Rotate(Vector3 angle) {
	return Rotate(angle.x, angle.y, angle.z);
}
Quaternion& Quaternion::Rotate(float X, float Y, float Z) {
	X *= DEG2RAD;
	Y *= DEG2RAD;
	Z *= DEG2RAD;

	float c2 = cos(Z * 0.5)
		, s2 = sin(Z * 0.5)
		, c1 = cos(Y * 0.5)
		, s1 = sin(Y * 0.5)
		, c0 = cos(X * 0.5)
		, s0 = sin(X * 0.5);

	x = c1 * c2 * s0 + s1 * s2 * c0;
	y = s1 * c2 * c0 - c1 * s2 * s0;
	z = c1 * s2 * c0 - s1 * c2 * s0;
	w = c1 * c2 * c0 + s1 * s2 * s0;
	
	return *this;
}
Vector3 Quaternion::ToEuler() {
	float v = (y*z) + (x*w);
	if (abs(v - 0.5) < 1e-12) {
		return Vector3(2 * atan2(y,x), M_PI / 2, 0 );
	}
	if (abs(v + 0.5) < 1e-12) {
		return Vector3(-2 * atan2(y,x), -M_PI / 2, 0 );
	}
	return Vector3(atan2(2 * (x*z - y*w), 1 - 2 * (z*z + w*w)),
		asin(2 * v),
		atan2(2 * (x*y - z*w), 1 - 2 * (y*y + w*w)));
}
std::string Quaternion::ToString() {
	std::stringstream ss;
	ss << "{ x:" << x << " y:" << y << " z:" << z << " w:" << w << " }";
	return ss.str();
}
void Quaternion::Print(std::string title) {
	std::cout << title << this->ToString() << std::endl;
}
